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
	SuperImagePatch(string id)
	{
		superImagePatchId = id;
	}
	SuperImagePatch(string id, Mat *bsip, Mat *osip)
	{
		superImagePatchId = id;
		setBinaryImagePatch(bsip);
		setOriginalImagePatch(osip);
	}


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
	//两个超图元进行比较，返回表示相似度的一个数(重写方法）
	double patchCompareWith(Patch *pSuperImagePatch, string featureType);
	*/
	//将超图元存入数据库中(重写方法）
	void savePatch(SQLiteHelper &sql_lite_helper) const;
private:
	string superImagePatchId;//超图元id，要唯一，用“OriginalImageId_“superImagePatch”_编号”组成
	vector<map<string, vector<double>>> features;//存储图元的各种特征
	//Mat *binarySuperImagePatch;//超图元二值化表示
	//Mat *originalSuperImagePatch;//超图元在原图像中的表示
	vector<Patch*> patchList;//超图元所对应的子图元列表；
};

#endif