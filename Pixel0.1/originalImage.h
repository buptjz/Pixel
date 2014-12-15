#ifndef ORIGINALIMAGE_H
#define ORIGINALIMAGE_H

#include "imagePatch.h"
#include<cxcore.h>
#include<highgui.h>
#include<iostream>
#include<string.h>
#include<list>

using namespace std;
using namespace cv;

class OriginalImage
{
public:
	OriginalImage(){}
	OriginalImage(string path, string originalImageId)
	{
		this->originalImageId = originalImageId;
		this->path = path;
		pOImage = 0;
	}
	OriginalImage(string originalImageId, string path, IplImage *pOImage)
	{
		this->originalImageId = originalImageId;
		this->path = path;
		this->pOImage = pOImage;
	}
	void setOriginalImageId(string id){ originalImageId = id; }
	void setPath(string s){ path = s; }
	void setImage(IplImage *pImage){ pOImage = pImage; }
	string getOriginalImageId() const { return originalImageId; }
	string getPath() const { return path; }
	IplImage* getImage() { return pOImage; }

	//�ָ�ͼƬ������СͼԪ�ļ���
	list<ImagePatch*> segmentImage();
	//��ͼƬ��Ϣ�������ݿ���
	void saveOriginalImage();
private:
	string originalImageId;//ͼƬ��id��ҪΨһ���á��ļ�����_ͼ���������
	string path;
	IplImage *pOImage;

};




#endif