#ifndef ORIGINALIMAGE_H
#define ORIGINALIMAGE_H

#include "imagePatch.h"
#include "sqlliteHelper.h"
#include<cxcore.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<string.h>
#include<vector>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
//class ImagePatch{
//public:
//	ImagePatch(string, void*, Rect r, Mat *, Mat *){
//		rect = r;
//	}
//	Rect getPosition(){ return rect; }
//private:
//	Rect rect;
//};
class OriginalImage
{
public:
	/*OriginalImage();
	OriginalImage(const string & path, const string & originalImageId);
	OriginalImage(const string & originalImageId, const string & path, Mat * const pOImage);*/

	OriginalImage(){}
	OriginalImage(const string & path, const string & originalImageId) :originalImageId(originalImageId), path(path), pOImage(0), regImage(NULL){}

	OriginalImage(const string &originalImageId) :originalImageId(originalImageId){ }

	OriginalImage(const string & originalImageId, const string & path, Mat
		* const pOImage) : originalImageId(originalImageId), path(path), pOImage(pOImage), regImage(NULL){}
	const string & getOriginalImageId() const { return originalImageId; }
	const string & getPath() const { return path; }
	const Mat * getImage() const { return pOImage; }
	void setOriginalImageId(const string & id){ originalImageId = id; }
	void setPath(const string & s){ path = s; }
	void setImage(Mat *pImage){ pOImage = pImage; }
	/*分割图片，返回小图元的集合*/
	vector<ImagePatch *> segmentImage(string segment_type);
	//将图片信息存入数据库中
	void saveOriginalImage()const;
	/* 显示不同区域*/
	void ShowRegion() const;
	/* 显示区域的矩形框*/
	void ShowRects(const vector<ImagePatch *> &) const;

protected:
	const Mat & prePareImage(Mat &, Mat & (*)(Mat &, Mat &)) const;
	/* 返回连通图*/
	const int segAlgorithm(Mat &, int (*)(Mat &, Mat &)) const;
	vector<Rect *> & getMetaInfos(vector<Rect *> &, int) const;
	vector<Rect *> & getMetaInfos(vector<vector<Point>> &, vector<Rect *> &) const;

private:
	string originalImageId;//图片的id，要唯一，用“文件夹名_图像名”组成
	string path;
	Mat *pOImage;
	Mat *regImage;
};

#endif