#include "qtThread.h"
#include "superImagePatch.h"
#include <io.h>
#include "tools.h"
#include "removeDuplicatePatchs.h"
#include "readSqllite.h"
#include "params.h"
#include "logDisplay.h"
#include "qt_pixel_main.h"
extern LogDisplay* logDisplay;
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
		logDisplay->logDisplay("Segmenting " + filename + "... ...");
		ori->setImage(pImage);

		//save originalImage into database 
		ori->saveOriginalImage();
		//segment OriginalImage object ori into patchs
   		vector<ImagePatch*> patchs = ori->segmentImage();

		logDisplay->logDisplay("Segment " + filename + " finished");
		for (int i = 0; i < patchs.size(); i++)
		{
			patchs[i]->savePatch();
		}
		logDisplay->logDisplay(filename + " saved in to database");
		logDisplay->logDisplay("Removing duplicate image patches in image: " + filename + " ... ...");
		//removeDuplicateImagePatchs  first time, just in one originalImage, return  vector of SuperImagePatch object
 		vector<SuperImagePatch*> sip = removeDuplicateImagePatchs(patchs);
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
	vector<SuperImagePatch*> fsip = removeDuplicateSuperImagePatchs(allSuperImagePatchs);
	logDisplay->logDisplay("Remove duplicate image patches in all super image patches  finished");
	//save superImagePatches into the database && update the superImagePatchId of table imagePatch in database
	vector<SuperImagePatch*>::iterator  itor = fsip.begin();
	while (itor != fsip.end())
	{
		SuperImagePatch* sip = (SuperImagePatch*)*itor;
		//here save superImagePatch
		sip->savePatch();
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
	const string featureType = Params::featureType;
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
	*segementedImagePatches = originalImageSegemented->segmentImage();
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
	*segementedSupeImagePatches = removeDuplicateImagePatchs(*segementedImagePatches);
	logDisplay->logDisplay("Remove duplicate image patches finished.");
	emit this->sig();
}
