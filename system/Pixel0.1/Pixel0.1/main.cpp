#include<iostream>
#include<fstream>
#include"superImagePatch.h"
#include "imagePatch.h"
#include "originalImage.h"
#include "jsonHelper.h"
#include "sqlliteHelper.h"
#include "removeDuplicatePatchs.h"
#include<string>
#include<highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include<cv.h>
#include<io.h>
#include "readSqllite.h"
#include "tools.h"
#include "surfMatch.h"
using namespace std;
using namespace cv;

//vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch*>&);
//vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>&);

int main(int agrc, char **agrv){
	/*
	fstream _file;
	_file.open("Pixel.db3", ios::in);
	if (!_file)
	{
		//create database
		int res = SQLiteHelper::OpenDB("./Pixel.db3");
		//create tables
		vector<const char*> tables;
		tables.push_back("originalImage(originalImageId varchar, path varchar)");
		tables.push_back("imagePatch(imagePatchId varchar, originalImageId varchar, superImagePatchId varchar, position varchar, binarySuperImagePatch blob, originalSuperImagePatch blob, features text)");
		tables.push_back("superImagePatch(superImagePatchId varchar, binarySuperImagePatch blob, originalSuperImagePatch blob, features text, imagePatchIdList text)");
		res = SQLiteHelper::CreateTables(tables);
	}
	else
	{
		//open database
		int res = SQLiteHelper::OpenDB("./Pixel.db3");
	}


	vector<SuperImagePatch*> allSuperImagePatchs;
	string path;//ͼ���ļ�·��
	string fileName = "all";//��ԭͼƬ���ļ�����
	string fileAddress = "C:/Users/xzw/Desktop/" + fileName;//�ļ���·��
	//string fileName = "TestImage";//��ԭͼƬ���ļ�����
	//string fileAddress = "D:/" + fileName;//�ļ���·��

	//�����ļ������ͼ���ļ�
	_finddata_t fileinfo;
	int handle = _findfirst((fileAddress + "/*.*").c_str(), &fileinfo);
	while (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
		_findnext(handle, &fileinfo);
	while (handle != -1)
	{
		//�����һ��ͼ����д���
		//=========================================================
		path = fileAddress + "/" + fileinfo.name;
		//����OriginalImage��Ķ���ori
		string originalImageId = fileName + "_" + fileinfo.name;
		OriginalImage *ori = new OriginalImage(path, originalImageId);
		
		Mat pImage = imread_and_preprocess(path.c_str());
		ori->setImage(&pImage);
		tool_show_mat(pImage, "originalImage");
		//��ori�ָ��õ�СͼԪ�ļ���patchs��������������ݿ�
		vector<ImagePatch*> patchs = ori->segmentImage();
	//	ori->saveOriginalImage();
		for (int i = 0; i < patchs.size(); i++)
		{
		//	patchs[i]->savePatch();
			tool_show_patch(patchs[i], to_string((long double)i));
		}


		//patchs������СͼԪ����һ��ȥ�أ�����ȥ�غ��SuperImagePatch��Ķ��󼯺�
		vector<SuperImagePatch*> sip = removeDuplicateImagePatchs(patchs);
		//=========================================================
		//�����о���һ��ȥ�صĳ�ͼԪ�洢�������ȴ�������һ��ȥ��
		vector<SuperImagePatch*>::iterator  itor = sip.begin();
		while (itor != sip.end())
		{
			allSuperImagePatchs.push_back(*itor++);
		}

		//�ͷ�vector<ImagePatch*> patchs�Ŀռ�
		for (int i = 0; i < patchs.size(); i++)
		{
			delete patchs[i];
		}
		//������һ��ԭͼ��
		if (_findnext(handle, &fileinfo) == -1) break;
	}
	_findclose(handle);


	//�Խ���һ��ȥ�غ�ĳ�ͼԪ�ٴ�ȥ�أ��������յ�SuperImagePatch��Ķ��󼯺�
	vector<SuperImagePatch*> fsip = removeDuplicateSuperImagePatchs(allSuperImagePatchs);

	//����ͼԪ�������ݿⲢ������ͼԪ��
	vector<SuperImagePatch*>::iterator  itor = fsip.begin();
	while (itor != fsip.end())
	{
		//������Ҫ�ѳ�ͼԪ���������ݿ��в�������ͼԪ���е�superImagePatchId
		((SuperImagePatch*)*itor)->savePatch();
		//
		itor++;
	}
	*/
	/*
	SuperImagePatch sip;
	giveVGeAPatch("D:/TestImage/demoLittle.jpg",sip);
   // giveVGeAPatch("/Users/wangjz/Desktop",sip);
	sip.savePatch();
	string superImageId = sip.getSuperImagePatchId();

	SuperImagePatch *psip = readSuperImagePatch(superImageId);
	tool_show_mat(*(psip->getOriginalImagePatch()), "sip");
	*/

test_surf_match_func();
	
	return 0;
}

