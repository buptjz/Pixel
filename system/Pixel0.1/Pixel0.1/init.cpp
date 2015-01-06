#include "init.h"

void init()
{
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
	if (access(fileName.c_str(), 0) == -1)//access�����ǲ鿴�ļ��ǲ��Ǵ���
	{
		mkdir(fileName.c_str());//��������ھ���mkdir����������
	}

		

}