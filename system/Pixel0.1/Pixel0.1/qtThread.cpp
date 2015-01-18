#include "qtThread.h"
#include "superImagePatch.h"
#include <io.h>
#include "tools.h"
#include "removeDuplicatePatchs.h"
#include "readSqllite.h"
#include "params.h"
#include "logDisplay.h"
#include "qt_pixel_main.h"
#include "readSqllite.h"
#include "executeSqllite.h"
#include "generation_algorithm.h"
extern LogDisplay* logDisplay;

#include <direct.h>
ImageLibThread::ImageLibThread(QString dirPath) : QThread()
{
	this->dirPath = dirPath;
}

void ImageLibThread::run()
{
	vector<SuperImagePatch*> allSuperImagePatchs;
	string path = dirPath.toStdString();//the file direction of originalImages
	if (path.empty() || path == "")
	{
		return;
	}
	std::vector<std::string> splitpath = split(path, "/");
	logDisplay->logDisplay("images are training ... ... ");
	string fileName = splitpath[splitpath.size() - 1];//name of the file which contains originalImages
	//traverse folder
	_finddata_t fileinfo;
	int handle = _findfirst((path + "/*.*").c_str(), &fileinfo);
	while (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
		_findnext(handle, &fileinfo);
	while (handle != -1)
	{
		//process a single image
		string filename = path + "/" + fileinfo.name;
		string originalImageId = fileName + "_" + fileinfo.name;
		OriginalImage *ori = new OriginalImage(filename, originalImageId);
		
		Mat *pImage = new Mat(imread_and_preprocess(filename.c_str()));
		if (pImage->data == NULL)
		{
			logDisplay->logDisplay("Can't parse image "  + filename);
			if (_findnext(handle, &fileinfo) == -1) break;
			continue;
		}
		logDisplay->logDisplay("Segmenting " + filename + "... ...");
		ori->setImage(pImage);

		//save originalImage into database 
		ori->saveOriginalImage();
		//segment OriginalImage object ori into patchs
   		vector<ImagePatch*> patchs = ori->segmentImage(Params::segment_type_for_batch_image);

		logDisplay->logDisplay("Segment " + filename + " finished");
		for (int i = 0; i < patchs.size(); i++)
		{
			patchs[i]->savePatch();
		}
		logDisplay->logDisplay(filename + " saved in to database");
		logDisplay->logDisplay("Removing duplicate image patches in image: " + filename + " ... ...");
		//removeDuplicateImagePatchs  first time, just in one originalImage, return  vector of SuperImagePatch object
 		vector<SuperImagePatch*> sip = removeDuplicateImagePatchs(patchs,Params::featureType_for_batch_image);
		logDisplay->logDisplay("Remove duplicate image patches in image: " + filename + " finished");
		//save the patchs which has been removed duplicate once, wait for the next time of removing duplicate operation
		vector<SuperImagePatch*>::iterator  itor = sip.begin();
		
		while (itor != sip.end())
		{
			allSuperImagePatchs.push_back(*itor++);
		}
		
		//release vector<ImagePatch*> patchs
		for (int i = 0; i < patchs.size(); i++)
		{
			delete patchs[i];
		}

		//traversing the next image
		if (_findnext(handle, &fileinfo) == -1) break;
	}
	_findclose(handle);

	logDisplay->logDisplay("Removing duplicate image patches in all super image patches  ... ...");
	//the second time of duplicate removal, finally obtain the collection of superImagePatch
	vector<SuperImagePatch*> fsip = removeDuplicateSuperImagePatchs(allSuperImagePatchs,Params::featureType_for_batch_image);
	logDisplay->logDisplay("Remove duplicate image patches in all super image patches  finished");
	//save superImagePatches into the database && update the superImagePatchId of table imagePatch in database
	vector<SuperImagePatch*>::iterator  itor = fsip.begin();
	while (itor != fsip.end())
	{
		SuperImagePatch* sip = (SuperImagePatch*)*itor;
		//here save superImagePatch
		sip->savePatch();
		//----------------------------------------------------------------------------------------------------------------------------------
		//save all super image patches into a file 
		string folder = "./superImagePatches";
		mkdir(folder.c_str());
		String filedir = folder + "/" + sip->getSuperImagePatchId() + ".jpg";
		imwrite(filedir, *sip->getOriginalImagePatch());
		//-----------------------------------------------------------------------------------------------------------------------------------
		//here update imagePatch table
		int res = updateImagePatchTable(*sip);
		if (res == -1)
		{
			logDisplay->logDisplay("Error: update the superImagePatchId of table imagePatch in database!");
		}
		itor++;

	}
	logDisplay->logDisplay("All super image patches have saved in to database.");
}


SearchBtnThread::SearchBtnThread(vector<pair<double, Patch*> >  *similarPatches, Patch * patchCompared) : QThread()
{
	this->similarPatches = similarPatches;
	this->patchCompared = patchCompared;
}

void SearchBtnThread::run()
{
	vector<Patch*> images = readAllSuperImagePatches();
	const string featureType = Params::featureType_for_search;
	size_t top_k = Params::top_k;
	*similarPatches = patchCompared-> patchCompareWith(images, featureType, top_k);
	emit sig();
}

SuperImagePatchItemclickedThread::SuperImagePatchItemclickedThread(SuperImagePatch *superImagePatch, vector<ImagePatch*> *imagePatchList) : QThread()
{
	this->superImagePatch = superImagePatch;
	this->imagePatchList = imagePatchList;
}

void SuperImagePatchItemclickedThread::run()
{
	vector<string> patchIdList = superImagePatch->getPatchIdList();
	ImagePatch* ip;
	for (int i = 0; i < patchIdList.size(); i++)
	{
		ip = readImagePatch(patchIdList[i]);
		(*imagePatchList).push_back(ip);
	}
	emit this->sig();
}


ImagePatchItemclickedThread::ImagePatchItemclickedThread(Rect position, String originalImagePath) : QThread()
{
	this->position = position;
	this->originalImagePath = originalImagePath;
}

void ImagePatchItemclickedThread::run()
{
	Mat pImage = imread_and_preprocess(originalImagePath.c_str());
	drawPatch(pImage, position);
}


SegmentBtnThread::SegmentBtnThread(OriginalImage* originalImageSegemented, vector<ImagePatch*>* segementedImagePatches) : QThread()
{
	this->originalImageSegemented = originalImageSegemented;
	this->segementedImagePatches = segementedImagePatches;
}

void SegmentBtnThread::run()
{
	logDisplay->logDisplay("Begin to segment image " + originalImageSegemented->getPath());
	*segementedImagePatches = originalImageSegemented->segmentImage(Params::segment_type_for_one_image);
	emit this->sig();
}

RemoveDuplicateBtnThread::RemoveDuplicateBtnThread(vector<ImagePatch*>* segementedImagePatches, vector<SuperImagePatch*> *segementedSupeImagePatches)
{
	this->segementedImagePatches = segementedImagePatches;
	this->segementedSupeImagePatches = segementedSupeImagePatches;
}

void RemoveDuplicateBtnThread::run()
{
	logDisplay->logDisplay("Removing dupicate image patches ... ...");
	*segementedSupeImagePatches = removeDuplicateImagePatchs(*segementedImagePatches,Params::featureType_for_one_image);
	logDisplay->logDisplay("Remove duplicate image patches finished.");
	emit this->sig();
}


SavePatches2DataBaseBtnThread::SavePatches2DataBaseBtnThread(OriginalImage* originalImageSegemented, vector<ImagePatch*>* segementedImagePatches, vector<SuperImagePatch*> *segementedSupeImagePatches)
{
	this->originalImageSegemented = originalImageSegemented;
	this->segementedImagePatches = segementedImagePatches;
	this->segementedSupeImagePatches = segementedSupeImagePatches;
}

void SavePatches2DataBaseBtnThread::run()
{
	/*
	string path = originalImageSegemented->getPath();
	string pattern = "/";
	vector<std::string>  splitstr = split(path, pattern);
	
	string imageName = splitstr[splitstr.size() - 1];
	string newPath = "./" + Params::defaultPath + "/" + imageName;
	string originalImageId = Params::defaultPath + "_" + imageName;
	originalImageSegemented->setOriginalImageId(originalImageId);
	originalImageSegemented->setPath(newPath);
	//creat file of newPath if not exist
	*/
	string newPath = originalImageSegemented->getPath();
	imwrite(newPath, *originalImageSegemented->getImage());
	logDisplay->logDisplay("Saved the image readed in window to " + newPath);

	originalImageSegemented->saveOriginalImage();
	logDisplay->logDisplay("Begining to save segemented image patches");
	if (segementedImagePatches->empty() || segementedImagePatches->size() == 0)
	{
		*segementedImagePatches = originalImageSegemented->segmentImage(Params::segment_type_for_batch_image);
	}
	for (int i = 0; i < segementedImagePatches->size(); i++)
	{
		(*segementedImagePatches)[i]->savePatch();
	}
	logDisplay->logDisplay("Saved segemented image patches");

	logDisplay->logDisplay("Begining to save segemented super image patches");
	if (segementedSupeImagePatches->empty() || segementedSupeImagePatches->size() == 0)
	{
		*segementedSupeImagePatches = removeDuplicateImagePatchs(*segementedImagePatches,Params::featureType_for_batch_image);
	}
	logDisplay->logDisplay("Saved segemented super image patches");
	for (int i = 0; i < segementedSupeImagePatches->size(); i++)
	{
		(*segementedSupeImagePatches)[i]->savePatch();
		updateImagePatchTable(*(*segementedSupeImagePatches)[i]);

	}

	logDisplay->logDisplay("Saved information into database successed!");
	//*segementedSupeImagePatches = removeDuplicateImagePatchs(*segementedImagePatches);
	//logDisplay->logDisplay("Remove duplicate image patches finished.");

}

ShowAllSuperImagePatchesBtnThread::ShowAllSuperImagePatchesBtnThread(vector<Patch*> * superImagePatchesInPageReadFromDatabase, int &startNumber, int &pageSize)
{
	this->superImagePatchesInPageReadFromDatabase = superImagePatchesInPageReadFromDatabase;
	this->startNumber = startNumber;
	this->pageSize = pageSize;
}

void ShowAllSuperImagePatchesBtnThread::run()
{
	logDisplay->logDisplay("Reading  a page of super image patches from database.");
	*superImagePatchesInPageReadFromDatabase = readPartSuperImagePatches(startNumber, pageSize);
	logDisplay->logDisplay("Read  a page of super image patches from database finished.");
	emit this->sig();
}

AddCategoryThread::AddCategoryThread(const string &category, Patch* superImagePatchRightButtonClicked2)
{
	this->category = category;
	this->superImagePatchRightButtonClicked2 = superImagePatchRightButtonClicked2;
}

void AddCategoryThread::run()
{
	logDisplay->logDisplay("Adding  category of the super image patches clicked into database.");
	addCategoryOfSuperImagePatch(category, (SuperImagePatch *)superImagePatchRightButtonClicked2);
	logDisplay->logDisplay("Added  category of the super image patches clicked into database finished.");
}

DeletePatchThread::DeletePatchThread(Patch * superImagePatchRightButtonClicked)
{
	this->superImagePatchRightButtonClicked = superImagePatchRightButtonClicked;
}

void DeletePatchThread::run()
{
	logDisplay->logDisplay("Deleting the super image patches clicked from database.");
	deleteAnSuperImagePatchAndItsImagePatches((SuperImagePatch*)superImagePatchRightButtonClicked);
	logDisplay->logDisplay("Deleted the super image patches clicked from database finished.");
	emit this->sig();
}


GenerateImageThread::GenerateImageThread(Patch * superImagePatchRightButtonClicked, Mat** generatedImage)
{
	this->superImagePatchRightButtonClicked = superImagePatchRightButtonClicked;
	this->generatedImage = generatedImage;
}

void GenerateImageThread::run()
{
	logDisplay->logDisplay("Generating a big image form the patch.");
	//调用生成大图像方法，有superImagePatchRightButtonClicked生成generatdImage
	*generatedImage = generat_rot(&superImagePatchRightButtonClicked->getOriginalImagePatch()->clone());
	//*generatedImage = new Mat(superImagePatchRightButtonClicked->getOriginalImagePatch()->clone());
	logDisplay->logDisplay("Generated a big image form the patch finished.");
	emit this->sig();
}