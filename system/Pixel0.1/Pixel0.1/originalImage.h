#ifndef ORIGINALIMAGE_H
#define ORIGINALIMAGE_H

#include "imagePatch.h"
#include<cxcore.h>
#include<highgui.h>
#include<iostream>
#include<string.h>
#include<vector>

using namespace std;
using namespace cv;

class OriginalImage
{
public:
	OriginalImage();
	OriginalImage(const string & path, const string & originalImageId);
	OriginalImage(const string & originalImageId, const string & path, Mat * const pOImage);
	const string & getOriginalImageId() const { return originalImageId; }
	const string & getPath() const { return path; }
	const Mat * getImage() const { return pOImage; }
	/*分割图片，返回小图元的集合*/
	vector<ImagePatch *> segmentImage() const;
	//将图片信息存入数据库中
	void saveOriginalImage() const;

protected:
	void setOriginalImageId(const string & id){ originalImageId = id; }
	void setPath(const string & s){ path = s; }
	void setImage(Mat *pImage){ pOImage = pImage; }
	/**/
	const Mat & prePareImage(Mat &) const;
	/* 输入连通图， 区域数，返回小图元的位置信息
	CvRect 创造语句:
	CvRect *rects = new CvRect[count]*/
	Rect & getMetaInfos(const Mat &, Rect &, int) const;

private:
	string originalImageId;//图片的id，要唯一，用“文件夹名_图像名”组成
	string path;
	Mat *pOImage;
};

#endif