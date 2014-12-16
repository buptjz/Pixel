#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<cv.h>
#include<map>
using namespace std;
using namespace cv;
//图元块类，小图元和超图元共有的基本方法
class Patch{
public:
	Patch(){};
	Patch(Mat *bip, Mat *oip)
	{
		binaryImagePatch = bip;
		originalImagePatch = oip;
	}
	Patch(vector< map< string, vector<double>  > > f, Mat *bip, Mat *oip) :Patch(bip, oip)
	{		
		features = f;
	}
	/*和当前图元进行比较
	*输入：待比较的图元，比较时使用的特征种类
	*输出：本图元和待比较的图元的相似度
	*/
	double patchCompareWith(Patch *pPatch, string featureType) ;
	//将小图元存入数据库中
	virtual void savePatch() =0;

	void setBinaryImagePatch(Mat *bip) { binaryImagePatch = bip; }
	void setOriginalImagePatch(Mat *oip) { originalImagePatch = oip; }
	void setFeatures(vector<map<string, vector<double>>> f){ features = f; }
	Mat* getBinaryImagePatch() const { return binaryImagePatch; }
	Mat* getOriginalImagePatch() const { return originalImagePatch; }
	vector<map<string, vector<double>>> getFeatures() { return features; }
private:
	Mat *binaryImagePatch;//小图元二值化表示
	Mat *originalImagePatch;//小图元在原图像中的表示
	vector<map<string, vector<double>>> features;//存储图元的各种特征
};


#endif