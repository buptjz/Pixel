#ifndef IMAGEPATCH_H
#define IMAGEPATCH_H
#include "patch.h"
#include<list>
#include<map>
//#include "originalImage.h"
//#include "superImagePatch.h"

#include<iostream>
#include<string>
#include<cv.h>
#include<highgui.h>
using namespace cv;
using namespace std;
class OriginalImage;
class SuperImagePatch;

class ImagePatch :public Patch
{
public:
	ImagePatch(){}
	ImagePatch(string id, OriginalImage* oi, Rect p)
	{
		imagePatchId = id;
		originalImage = oi;
		position = p;
	}
	ImagePatch(string id, OriginalImage* oi, Rect p, Mat *bip, Mat *oip)
	{
		imagePatchId = id;
		originalImage = oi;
		position = p;
		binaryImagePatch = bip;
		originalImagePatch = oip;
	}
	void setImpagePatchId(string id){ imagePatchId = id; }
	void setOriginalImage(OriginalImage *poi) { originalImage = poi; }
	void setPosition(Rect ps) { position = ps;  }
	void setBinaryImagePatch(Mat *bip) { binaryImagePatch = bip; }
	void setOriginalImagePatch(Mat *oip) { originalImagePatch = oip;  }
	void setSuperImagePatch(SuperImagePatch *sip) { superImagePatch = sip;  }
	void setFeatures(list<map<string, vector<double>>> f){ features = f; }

	string getImagePatchId() const{ return imagePatchId; }
	OriginalImage* getOriginalImage() const{ return originalImage; }
	Rect getPosition() { 	return position; }
	Mat* getBinaryImagePatch() const { return binaryImagePatch; }
	Mat* getOriginalImagePatch() const { return originalImagePatch; }
	SuperImagePatch* getSuperImagePatch() const { return superImagePatch;  }
	list<map<string, vector<double>>> getFeatures() { return features; }

	//����СͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����
	double patchCompareWith(Patch *pImagePatch, string featureType);
	//��СͼԪ�������ݿ���
	void savePatch();


private:
	string imagePatchId;//СͼԪid��ҪΨһ���á�OriginalImageId_imagePath_��š����
	OriginalImage* originalImage;//СͼԪ������ͼ��
	Rect position;//СͼԪ��ͼ���е�λ�ã����Ͻǵ����꣬���½ǵ����꣩
	Mat *binaryImagePatch;//СͼԪ��ֵ����ʾ
	Mat *originalImagePatch;//СͼԪ��ԭͼ���еı�ʾ
	SuperImagePatch *superImagePatch;//СͼԪ����Ӧ�ĳ�ͼԪ
	list<map<string, vector<double>>> features;//�洢ͼԪ�ĸ�������
};


#endif