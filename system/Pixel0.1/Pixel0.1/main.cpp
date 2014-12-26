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
//#include<io.h>
#include "readSqllite.h"
using namespace std;
using namespace cv;

//vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch*>&);
//vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>&);

int main(int agrc, char **agrv){
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
		tables.push_back("superImagePatch(superImagePatchId varchar, binarySuperImagePatch blob, originalSuperImagePatch blob, features text)");
		res = SQLiteHelper::CreateTables(tables);
	}
	else
	{
		//open database
		int res = SQLiteHelper::OpenDB("./Pixel.db3");
	}

	/*//������������
	//����cvLoadImage()�ĵ�1 ��������ͼ���ļ���·��. ��2 �������Ƕ�ȡͼ��ķ�ʽ:-1 ��ʾ����ͼ�������������ȡ,1 ��ʾǿ�Ʋ�ɫ��,0 ��ʾǿ�ƻ�ֵ��.
	IplImage* image = cvLoadImage("D:\\demo.jpg", -1);
	if (image == NULL)
	{
	cout << "�޷���ȡͼ������!" << endl;
	return -1;
	}
	//�ú����Ĺ����ǰ���ָ����ʽ����һ������,������ʾͼ�񡣵�1 �������Ǵ��ڵ�����,�Լ������������ã���2 ��������ʾ���ڵĴ�С���Զ�����ͼ��ߴ���仯
	cvNamedWindow("ͼ����ʾ", CV_WINDOW_AUTOSIZE);
	//�ú����Ĺ�������ָ���Ĵ�������ʾͼ�񡣵�1 ����������ʾͼ�񴰿ڵ�����,��2 ��������Ҫ��ʾ��ͼ��
	cvShowImage("ͼ����ʾ", image);
	//�ú����Ĺ����ǽ�ͼ�����Ϊ����1 �������Ǳ����·��,�Լ�������������·��;��2 ��������Ҫ�����ͼ��
	cvSaveImage("D:\\saveImage.jpg", image);
	cvWaitKey(0);//һֱ�ȴ�����û�����Ļ�ͼ����������ʾ
	cvReleaseImage(&image);//�ͷ�ͼ���ڴ�
	cvDestroyWindow("ͼ����ʾ");//���ٴ�����Դ
	*/

	/*
	vector<SuperImagePatch*> allSuperImagePatchs;
	string path;//ͼ���ļ�·��
	string fileName = "TestImage";//��ԭͼƬ���ļ�����
	string fileAddress = "D:/" + fileName;//�ļ���·��

	//�����ļ������ͼ���ļ�
	_finddata_t fileinfo;
	int handle = _findfirst((fileAddress + "/*").c_str(), &fileinfo);
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
		Mat pImage = imread(path.c_str(), -1);
		ori->setImage(&pImage);

		//��ori�ָ��õ�СͼԪ�ļ���patchs��������������ݿ�
		vector<ImagePatch*> patchs = ori->segmentImage();
		ori->saveOriginalImage();
		for (int i = 0; i < patchs.size(); i++)
		{
			patchs[i]->savePatch();
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

	SuperImagePatch sip;
//	giveVGeAPatch("D:/TestImage/demoLittle.jpg",sip);
    giveVGeAPatch("/Users/wangjz/Desktop",sip);
	sip.savePatch();
	string superImageId = sip.getSuperImagePatchId();

	SuperImagePatch *psip = readSuperImagePatch(superImageId);

	return 0;
}

