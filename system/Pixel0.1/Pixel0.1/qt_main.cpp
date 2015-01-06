#include "qt_pixel_main.h"
#include <QtWidgets/QApplication>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "sqlliteHelper.h"
#include<string>
#include<cv.h>
#include<io.h>
#include "readSqllite.h"
#include "tools.h"
#include "params.h"
#include<fstream>
#include <direct.h>
#include "logDisplay.h"
extern LogDisplay* logDisplay;

using namespace cv;
int main(int argc, char *argv[])
{
	
	Params::top_k =5;
	Params::patch_pixel_min=0.01;
	Params::shape_context_compare_1_thres = 0.2;
	Params::shape_context_compare_2_thres = 0.2;
	Params::featureType = Params::SURF;//featureType used 
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
	
	//create a default file to put images which users want to add into database from external
	string fileName = Params::defaultPath;
	if (access(fileName.c_str(), 0) == -1)//access函数是查看文件是不是存在
	{
		mkdir(fileName.c_str());//如果不存在就用mkdir函数来创建
	}

	QApplication a(argc, argv);
	qt_Pixel_Main w;
	w.show();
	return a.exec();
	return a.exec();
}
