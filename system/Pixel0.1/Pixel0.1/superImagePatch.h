#ifndef SUPERIMAGEPATCH_H
#define SUPERIMAGEPATCH_H
#include "patch.h"
#include "originalImage.h"

#include<iostream>
#include<string.h>
#include<cv.h>
#include<highgui.h>
#include<map>
#include<list>
using namespace cv;
using namespace std;


class SuperImagePatch :Patch
{
public:
	SuperImagePatch(){}
	SuperImagePatch(string id)
	{
		superImagePatchId = id;
	}
	SuperImagePatch(string id, Mat *bsip, Mat *osip)
	{
		superImagePatchId = id;
		binarySuperImagePatch = bsip;
		originalSuperImagePatch = osip;
	}


	void setSuperImagePatchId(string sip) { superImagePatchId = sip; }
	void setFeatures(list<map<string, vector<double>>> f){ features = f; }
	void setBinarySuperImagePatch(Mat *bsip) { binarySuperImagePatch = bsip; };
	void setOriginalSuperImagePatch(Mat *osip) { originalSuperImagePatch = osip; }
	void setPatchList(list<Patch*> pl) { patchList = pl; }

	string getSuperImagePatchId() const { return superImagePatchId; }
	list<map<string, vector<double>>> getFeatures() { return features; }
	Mat* getBinarySuperImagePatch() { return binarySuperImagePatch; }
	Mat* getOriginalSuperImagePatch() { return originalSuperImagePatch; }
	list<Patch*> getPatchList() { return patchList; }

	//������ͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����(��д������
	double patchCompareWith(Patch *pSuperImagePatch, string featureType);
	//����ͼԪ�������ݿ���(��д������
	void savePatch();
private:
	string superImagePatchId;//��ͼԪid��ҪΨһ���á�OriginalImageId_��superImagePatch��_��š����
	list<map<string, vector<double>>> features;//�洢ͼԪ�ĸ�������
	Mat *binarySuperImagePatch;//��ͼԪ��ֵ����ʾ
	Mat *originalSuperImagePatch;//��ͼԪ��ԭͼ���еı�ʾ
	list<Patch*> patchList;//��ͼԪ����Ӧ����ͼԪ�б�
};

#endif