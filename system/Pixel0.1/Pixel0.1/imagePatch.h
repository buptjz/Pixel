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

	//两个小图元进行比较，返回表示相似度的一个数
	double patchCompareWith(Patch *pImagePatch, string featureType);
	//将小图元存入数据库中
	void savePatch();


private:
	string imagePatchId;//小图元id，要唯一，用“OriginalImageId_imagePath_编号”组成
	OriginalImage* originalImage;//小图元所属的图像
	Rect position;//小图元在图像中的位置（左上角点坐标，右下角点坐标）
	Mat *binaryImagePatch;//小图元二值化表示
	Mat *originalImagePatch;//小图元在原图像中的表示
	SuperImagePatch *superImagePatch;//小图元所对应的超图元
	list<map<string, vector<double>>> features;//存储图元的各种特征
};


#endif