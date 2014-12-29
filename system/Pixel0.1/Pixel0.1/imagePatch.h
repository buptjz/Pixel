#ifndef IMAGEPATCH_H
#define IMAGEPATCH_H
#include "patch.h"
#include<vector>
#include<map>
#include "sqlliteHelper.h"
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
	ImagePatch():originalImage(NULL),superImagePatch(NULL){}
	ImagePatch(string id, OriginalImage* oi, Rect p):imagePatchId(id),originalImage(oi),position(p),superImagePatch(NULL){}
	ImagePatch(string id, OriginalImage* oi, Rect p, Mat *bip, Mat *oip):imagePatchId(id),originalImage(oi),position(p),superImagePatch(NULL)
	{
		this->setBinaryImagePatch(bip);
		this->setOriginalImagePatch(oip);
	}
	ImagePatch(ImagePatch &rhd):Patch(rhd),position(rhd.position),imagePatchId(rhd.imagePatchId),originalImage(rhd.originalImage),superImagePatch(rhd.superImagePatch){}

	void setImpagePatchId(string id){ imagePatchId = id; }
	void setOriginalImage(OriginalImage *poi) { originalImage = poi; }
	void setPosition(Rect ps) { position = ps;  }
	//void setBinaryImagePatch(Mat *bip) { binaryImagePatch = bip; }
	//void setOriginalImagePatch(Mat *oip) { originalImagePatch = oip;  }
	void setSuperImagePatch(SuperImagePatch *sip) {superImagePatch = sip; }
	//void setFeatures(vector<map<string, vector<double>>> f){ features = f; }

	string getImagePatchId() const{ return imagePatchId; }
	OriginalImage* getOriginalImage() const{ return originalImage; }
	Rect getPosition() { 	return position; }
	//Mat* getBinaryImagePatch() const { return binaryImagePatch; }
	//Mat* getOriginalImagePatch() const { return originalImagePatch; }
	SuperImagePatch* getSuperImagePatch() const { return superImagePatch;  }
	//vector<map<string, vector<double>>> getFeatures() { return features; }

	/*
	//����СͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����
	double patchCompareWith(Patch *pImagePatch, string featureType);
	*/
	//��СͼԪ�������ݿ���
	void savePatch() const;
private:
	string imagePatchId;//СͼԪid��ҪΨһ���á�OriginalImageId_"imagePatch"_��š����
	OriginalImage* originalImage;//СͼԪ������ͼ��
	Rect position;//СͼԪ��ͼ���е�λ�ã����Ͻǵ����꣬���½ǵ����꣩
	//Mat *binaryImagePatch;//СͼԪ��ֵ����ʾ
	//Mat *originalImagePatch;//СͼԪ��ԭͼ���еı�ʾ
	SuperImagePatch *superImagePatch;//СͼԪ����Ӧ�ĳ�ͼԪ
	//vector<map<string, vector<double>>> features;//�洢ͼԪ�ĸ�������
};


#endif