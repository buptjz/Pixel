#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<cv.h>
#include<map>
using namespace std;
using namespace cv;
//ͼԪ���࣬СͼԪ�ͳ�ͼԪ���еĻ�������
class Patch{
public:
	Patch() :binaryImagePatch(NULL), originalImagePatch(NULL){}
	Patch(Mat *bip, Mat *oip) :binaryImagePatch(bip), originalImagePatch(oip){	}
	Patch(vector< map< string, vector<double>  > > f, Mat *bip, Mat *oip) :features(f),binaryImagePatch(bip), originalImagePatch(oip){}
	
	/*�͵�ǰͼԪ���бȽ�
	*���룺���Ƚϵ�ͼԪ���Ƚ�ʱʹ�õ���������
	*�������ͼԪ�ʹ��Ƚϵ�ͼԪ�����ƶ�
	*/
	virtual double patchCompareWith(Patch *pPatch, string featureType) ;
	//��СͼԪ�������ݿ���
	virtual void savePatch() =0;

	void setBinaryImagePatch(Mat *bip) { binaryImagePatch = bip; }
	void setOriginalImagePatch(Mat *oip) { originalImagePatch = oip; }
	void setFeatures(vector<map<string, vector<double>>> f){ features = f; }
	Mat* getBinaryImagePatch() const { return binaryImagePatch; }
	Mat* getOriginalImagePatch() const { return originalImagePatch; }
	vector<map<string, vector<double>>> getFeatures() { return features; }
private:
	Mat *binaryImagePatch;//СͼԪ��ֵ����ʾ
	Mat *originalImagePatch;//СͼԪ��ԭͼ���еı�ʾ
	vector<map<string, vector<double>>> features;//�洢ͼԪ�ĸ�������
};


#endif