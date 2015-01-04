#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QtCore/QThread>
#include "patch.h"
#include "superImagePatch.h"
using namespace std;
using namespace cv;

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

class SearchBtnThread : public QThread
{
	Q_OBJECT
public:
	SearchBtnThread(vector<pair<double, Patch*> >  *similarPatches, Patch * patchCompared);
	~SearchBtnThread(){};
	vector<pair<double, Patch*> >  *similarPatches;
	Patch * patchCompared;
protected:
	void run();
signals:
	void sig();
};

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

#endif