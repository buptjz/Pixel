#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<vector>
#include<cv.h>
using namespace std;
using namespace cv;
//ͼԪ���࣬СͼԪ�ͳ�ͼԪ���еĻ�������
class Patch{
public:
	/*�͵�ǰͼԪ���бȽ�
	*���룺���Ƚϵ�ͼԪ���Ƚ�ʱʹ�õ���������
	*�������ͼԪ�ʹ��Ƚϵ�ͼԪ�����ƶ�
	*/
	virtual double patchCompareWith(Patch *pPatch, vector<string> featureType) = 0;
	//��СͼԪ�������ݿ���
	virtual void savePatch() = 0;
private:
	Mat *binaryImagePatch;//СͼԪ��ֵ����ʾ
	Mat *originalImagePatch;//СͼԪ��ԭͼ���еı�ʾ
};


#endif