#ifndef SUPERIMAGEPATCH_H
#define SUPERIMAGEPATCH_H
#include "patch.h"
#include "originalImage.h"

#include<iostream>
#include<string.h>
#include<cv.h>
#include<highgui.h>
#include<map>
#include<vector>
using namespace cv;
using namespace std;


class SuperImagePatch :public Patch
{
public:
	SuperImagePatch(){}
	SuperImagePatch(string id):superImagePatchId(id){}
	SuperImagePatch(string id, Mat *bsip, Mat *osip):Patch(bsip,osip),superImagePatchId(id){}


	void setSuperImagePatchId(string sip) { superImagePatchId = sip; }
	//void setFeatures(vector<map<string, vector<double>>> f){ features = f; }
	//void setBinarySuperImagePatch(Mat *bsip) { binarySuperImagePatch = bsip; };
	//void setOriginalSuperImagePatch(Mat *osip) { originalSuperImagePatch = osip; }
	void setPatchList(vector<Patch*> pl) { patchList = pl; }

	string getSuperImagePatchId() const { return superImagePatchId; }
	vector<map<string, vector<double>>> getFeatures() { return features; }
	//Mat* getBinarySuperImagePatch() { return binarySuperImagePatch; }
	//Mat* getOriginalSuperImagePatch() { return originalSuperImagePatch; }
	vector<Patch*> getPatchvector() { return patchList; }
	/*
	//������ͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����(��д������
	double patchCompareWith(Patch *pSuperImagePatch, string featureType);
	*/
	//����ͼԪ�������ݿ���(��д������
	void savePatch(SQLiteHelper &sql_lite_helper) const;
private:
	string superImagePatchId;//��ͼԪid��ҪΨһ���á�OriginalImageId_��superImagePatch��_��š����
	vector<map<string, vector<double>>> features;//�洢ͼԪ�ĸ�������
	//Mat *binarySuperImagePatch;//��ͼԪ��ֵ����ʾ
	//Mat *originalSuperImagePatch;//��ͼԪ��ԭͼ���еı�ʾ
	vector<Patch*> patchList;//��ͼԪ����Ӧ����ͼԪ�б�
};

#endif