#ifndef ORIGINALIMAGE_H
#define ORIGINALIMAGE_H

#include "imagePatch.h"
#include "sqlliteHelper.h"
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
	/*OriginalImage();
	OriginalImage(const string & path, const string & originalImageId);
	OriginalImage(const string & originalImageId, const string & path, Mat * const pOImage);*/

	OriginalImage();
	OriginalImage(const string &originalImageId) :originalImageId(originalImageId){ }
	OriginalImage(const string & path, const string & originalImageId) :originalImageId(originalImageId), path(path), pOImage(0)	{}
	OriginalImage(const string & originalImageId, const string & path, Mat
	* const pOImage) : originalImageId(originalImageId), path(path), pOImage(pOImage){}
	const string & getOriginalImageId() const { return originalImageId; }
	const string & getPath() const { return path; }
	const Mat * getImage() const { return pOImage; }
	void setOriginalImageId(const string & id){ originalImageId = id; }
	void setPath(const string & s){ path = s; }
	void setImage(Mat *pImage){ pOImage = pImage; }
	/*�ָ�ͼƬ������СͼԪ�ļ���*/
	vector<ImagePatch *> segmentImage() const;
	//��ͼƬ��Ϣ�������ݿ���
	void saveOriginalImage(SQLiteHelper &sql_lite_helper) const
	{
		std::stringstream str_sql;
		str_sql << "insert into originalImage values(";
		str_sql << originalImageId << "," << path<< ");";
		std::string str = str_sql.str();
		sql_lite_helper.Insert(str.c_str());
	}

private:
	string originalImageId;//ͼƬ��id��ҪΨһ���á��ļ�����_ͼ���������
	string path;
	Mat *pOImage;
};

#endif