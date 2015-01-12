#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QtCore/QThread>
#include "patch.h"
#include "superImagePatch.h"
using namespace std;
using namespace cv;

//open imge liberary in which images to be segmented and add into database
class ImageLibThread : public QThread
{
	Q_OBJECT
public:
	ImageLibThread(QString dirPath);
	~ImageLibThread(){};
	QString dirPath;
protected:
	void run();
signals:
	void sig();
};

//search super image patches in the database
class SearchBtnThread : public QThread
{
	Q_OBJECT
public:
	SearchBtnThread(vector<pair<double, Patch*> >  *similarPatches, Patch * patchCompared);
	~SearchBtnThread(){};
	vector<pair<double, Patch*> >  *similarPatches = NULL;
	Patch * patchCompared = NULL;
protected:
	void run();
signals:
	void sig();
};

//find image patches reflect to the super image patch clicked
class SuperImagePatchItemclickedThread : public QThread
{
	Q_OBJECT
public:
	SuperImagePatchItemclickedThread(SuperImagePatch *superImagePatch, vector<ImagePatch*> *imagePatchList);
	~SuperImagePatchItemclickedThread(){};
	SuperImagePatch *superImagePatch;
	vector<ImagePatch*> *imagePatchList;
protected:
	void run();
signals: 
	void sig();
};

//display the image patch clicked in the original image
class ImagePatchItemclickedThread : public QThread
{
	Q_OBJECT
public:
	ImagePatchItemclickedThread(Rect position, String originalImagePath);
	Rect position;
	String originalImagePath;
protected:
	void run();
};


//segment an image read from temp path
class SegmentBtnThread : public QThread
{
	Q_OBJECT
public:
	SegmentBtnThread(OriginalImage* OriginalImageSegemented, vector<ImagePatch*>* segementedImagePatches);
	OriginalImage* originalImageSegemented = NULL;
	vector<ImagePatch*> *segementedImagePatches = NULL;
protected:
	void run();
signals:
	void sig();
};

//segment an image read from temp path
class RemoveDuplicateBtnThread : public QThread
{
	Q_OBJECT
public:
	RemoveDuplicateBtnThread(vector<ImagePatch*>* segementedImagePatches, vector<SuperImagePatch*> *segementedSupeImagePatches);
	vector<SuperImagePatch*> *segementedSupeImagePatches = NULL;
	vector<ImagePatch*> *segementedImagePatches = NULL;
protected:
	void run();
signals:
	void sig();
};

//save an image and its imformation into database
class SavePatches2DataBaseBtnThread : public QThread
{
	Q_OBJECT
public:
	SavePatches2DataBaseBtnThread(OriginalImage* originalImageSegemented, vector<ImagePatch*>* segementedImagePatches, vector<SuperImagePatch*> *segementedSupeImagePatches);
	OriginalImage* originalImageSegemented = NULL;
	vector<SuperImagePatch*> *segementedSupeImagePatches = NULL;
	vector<ImagePatch*> *segementedImagePatches = NULL;
protected:
	void run();
};

//show all super image patches  in page
class ShowAllSuperImagePatchesBtnThread : public QThread
{
	Q_OBJECT
public:
	ShowAllSuperImagePatchesBtnThread(vector<Patch*> * superImagePatchesInPageReadFromDatabase, int &startNumber, int &pageSize);
	~ShowAllSuperImagePatchesBtnThread(){};
	vector<Patch*> * superImagePatchesInPageReadFromDatabase = NULL;
	int startNumber;
	int pageSize;
protected:
	void run();
signals:
	void sig();
};


//Save category of this super image patch into database
class AddCategoryThread : public QThread
{
	Q_OBJECT
public:
	AddCategoryThread(const string &category, Patch* superImagePatchRightButtonClicked2);
	~AddCategoryThread(){};
	string category;
	Patch* superImagePatchRightButtonClicked2 = NULL;
protected:
	void run();
};

//Delete the super image patch  clicked from database
class DeletePatchThread : public QThread
{
	Q_OBJECT
public:
	DeletePatchThread(Patch * superImagePatchRightButtonClicked);
	~DeletePatchThread(){};
	Patch* superImagePatchRightButtonClicked = NULL;
protected:
	void run();
signals:
	void sig();
};

#endif

