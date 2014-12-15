#ifndef SUPERIMAGEPATCH_H
#define SUPERIMAGEPATCH_H
#include "patch.h"
#include "originalImage.h"
#include "position.h"

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

	//两个超图元进行比较，返回表示相似度的一个数(重写方法）
	double patchCompareWith(Patch *pSuperImagePatch, string featureType);
	//将超图元存入数据库中(重写方法）
	void savePatch();
private:
	string superImagePatchId;//超图元id，要唯一，用“OriginalImageId_“superImagePatch”_编号”组成
	list<map<string, vector<double>>> features;//存储图元的各种特征
	Mat *binarySuperImagePatch;//超图元二值化表示
	Mat *originalSuperImagePatch;//超图元在原图像中的表示
	list<Patch*> patchList;//超图元所对应的子图元列表；
};

#endif