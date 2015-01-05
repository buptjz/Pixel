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
#endif