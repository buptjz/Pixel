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
	const Mat * getRegImage() const { return regImage; }
	void setOriginalImageId(const string & id){ originalImageId = id; }
	void setPath(const string & s){ path = s; }
	void setImage(Mat *pImage){ pOImage = pImage; }
	/*�ָ�ͼƬ������СͼԪ�ļ���*/
	vector<ImagePatch *> segmentImage(string segment_type);
	int get_connected_map(string segment_type);
	vector<ImagePatch*> get_patches(int connect_num);
	//��ͼƬ��Ϣ�������ݿ���
	void saveOriginalImage()const;
	/* ��ʾ��ͬ����*/
	void ShowRegion() const;
	/* ��ʾ����ľ��ο�*/
	void ShowRects(const vector<ImagePatch *> &) const;

protected:
	const Mat & prePareImage(Mat &, Mat & (*)(Mat &, Mat &)) const;
	/* ������ͨͼ*/
	const int segAlgorithm(Mat &, int (*)(Mat &, Mat &)) const;
	vector<Rect *> & getMetaInfos(vector<Rect *> &, int) const;
	vector<Rect *> & getMetaInfos(vector<vector<Point>> &, vector<Rect *> &) const;

private:
	string originalImageId;//ͼƬ��id��ҪΨһ���á��ļ�����_ͼ���������
	string path;
	Mat *pOImage;
	Mat *regImage;
};

#endif