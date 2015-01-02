#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<cv.h>
#include<map>
#include "sqlliteHelper.h"
using namespace std;
using namespace cv;
//ͼԪ���࣬СͼԪ�ͳ�ͼԪ���еĻ�������
class Patch{
public:
	Patch():binaryImagePatch(NULL),originalImagePatch(NULL){};
	Patch(Mat *bip, Mat *oip):binaryImagePatch(bip),originalImagePatch(oip){}
	Patch( map< string, string  >  f, Mat *bip, Mat *oip):binaryImagePatch(bip),originalImagePatch(oip),features(f){}
	Patch(Patch &rhd):binaryImagePatch(new Mat()),originalImagePatch(new Mat()),features(rhd.features)
	{
		rhd.binaryImagePatch->copyTo(*binaryImagePatch);
		rhd.originalImagePatch->copyTo(*originalImagePatch);
	}
	Patch& operator=(Patch &rhd)
	{
		if(this == &rhd)
			return *this;
		delete_members();
		binaryImagePatch = new Mat(rhd.binaryImagePatch->clone());
		originalImagePatch = new Mat(rhd.originalImagePatch->clone());
		features = rhd.features;
		return *this;
	}
	virtual ~Patch(){delete_members();}
	
	/*�͵�ǰͼԪ���бȽ�
	*���룺���Ƚϵ�ͼԪ���Ƚ�ʱʹ�õ���������
	*�������ͼԪ�ʹ��Ƚϵ�ͼԪ�����ƶ�
	*/
	double patchCompareWith(Patch *pPatch, const string featureType) ;
	vector<double> patchCompareWith(const vector<Patch*>& images, const string featureType) ;
	vector<pair<double,Patch*> > patchCompareWith(const vector<Patch*>& images, const string featureType, size_t top_k) ;
	//��СͼԪ�������ݿ���
	virtual void savePatch() const = 0;

	void setBinaryImagePatch(Mat *bip) 
	{
		if(binaryImagePatch != NULL)
			delete binaryImagePatch;
		binaryImagePatch = bip; 
	}
	void setOriginalImagePatch(Mat *oip) 
	{ 
		if(originalImagePatch != NULL)
			delete originalImagePatch;
		originalImagePatch = oip; 
	}
	void setFeatures(map<string, string > f){ features = f; }
	void addFeature(pair<string, string> f){ features.insert(f); }
	Mat* getBinaryImagePatch() const { return binaryImagePatch; }
	Mat* getOriginalImagePatch() const { return originalImagePatch; }
	map<string, string > getFeatures() const { return features; }
private:
	void delete_members()
	{
		if(NULL != binaryImagePatch)
			delete binaryImagePatch;
		if(NULL != originalImagePatch)
			delete originalImagePatch;
	}

	Mat *binaryImagePatch;//СͼԪ��ֵ����ʾ
	Mat *originalImagePatch;//СͼԪ��ԭͼ���еı�ʾ
	map<string, string > features;//�洢ͼԪ�ĸ�������
};


#endif