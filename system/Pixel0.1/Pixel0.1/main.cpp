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
	string path;//图像文件路径
	string fileName = "all";//放原图片的文件夹名
	string fileAddress = "C:/Users/xzw/Desktop/" + fileName;//文件夹路径
	//string fileName = "TestImage";//放原图片的文件夹名
	//string fileAddress = "D:/" + fileName;//文件夹路径

	//遍历文件夹里的图像文件
	_finddata_t fileinfo;
	int handle = _findfirst((fileAddress + "/*.*").c_str(), &fileinfo);
	while (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
		_findnext(handle, &fileinfo);
	while (handle != -1)
	{
		//下面对一幅图像进行处理
		//=========================================================
		path = fileAddress + "/" + fileinfo.name;
		//构造OriginalImage类的对象ori
		string originalImageId = fileName + "_" + fileinfo.name;
		OriginalImage *ori = new OriginalImage(path, originalImageId);
		
		Mat pImage = imread_and_preprocess(path.c_str());
		ori->setImage(&pImage);
		tool_show_mat(pImage, "originalImage");
		//将ori分割后得到小图元的集合patchs，并将其存入数据库
		vector<ImagePatch*> patchs = ori->segmentImage();
	//	ori->saveOriginalImage();
		for (int i = 0; i < patchs.size(); i++)
		{
		//	patchs[i]->savePatch();
			tool_show_patch(patchs[i], to_string((long double)i));
		}


		//patchs中所有小图元进行一次去重，返回去重后的SuperImagePatch类的对象集合
		vector<SuperImagePatch*> sip = removeDuplicateImagePatchs(patchs);
		//=========================================================
		//将所有经过一次去重的超图元存储起来，等待进行下一次去重
		vector<SuperImagePatch*>::iterator  itor = sip.begin();
		while (itor != sip.end())
		{
			allSuperImagePatchs.push_back(*itor++);
		}

		//释放vector<ImagePatch*> patchs的空间
		for (int i = 0; i < patchs.size(); i++)
		{
			delete patchs[i];
		}
		//遍历下一幅原图像
		if (_findnext(handle, &fileinfo) == -1) break;
	}
	_findclose(handle);


	//对进行一次去重后的超图元再次去重，返回最终的SuperImagePatch类的对象集合
	vector<SuperImagePatch*> fsip = removeDuplicateSuperImagePatchs(allSuperImagePatchs);

	//将超图元存入数据库并更新子图元表
	vector<SuperImagePatch*>::iterator  itor = fsip.begin();
	while (itor != fsip.end())
	{
		//这里需要把超图元都存入数据库中并更新子图元表中的superImagePatchId
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

