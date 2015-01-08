#include "sqlliteHelper.h"
#include "originalImage.h"
#include "imagePatch.h"
#include "superImagePatch.h"
#include "sqlliteHelper.h"
#include <opencv2/highgui/highgui.hpp>
#include "jsonHelper.h"
#include <cv.h>
#include<highgui.h>
#include<iostream>
#include "tools.h"
#include "logDisplay.h"
extern LogDisplay* logDisplay;
using namespace cv;

OriginalImage* readOriginalImage(const string &originalImageId)
{
	OriginalImage* poi;
	string sql = "select path from originalImage where originalImageId = '" + originalImageId +"'";
	char *errmsg = NULL;
	char** dbResult = NULL;
	int nRow, nColumn;
	//int result = sqlite3_get_table(SQLiteHelper::getSqlite3(), sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
	int result = sqlite3_get_table(SQLiteHelper::sqlite_db_, sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
	
	//��ѯ�ɹ�
	int index = nColumn; //dbResult ǰ���һ���������ֶ����ƣ��� nColumn ������ʼ��������������

	string path = dbResult[1];// dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ�����涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ
	Mat pOImage = imread(path.c_str(), -1);
	if (pOImage.data == NULL)
	{
		logDisplay->logDisplay("Error in reading originalImage for database");
	}
	poi = new OriginalImage(originalImageId, path, &pOImage);

	sqlite3_free_table(dbResult);//�ͷŲ�ѯ�ռ�
	return poi;

}

ImagePatch* readImagePatch(string imagePatchId)
{
	ImagePatch* pip;
	string originalImageId ;
	string superImagePatchId;
	string positionStr;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;

	Mat *binaryImagePatch = new Mat;
	Mat *originalImagePatch = new Mat;
	map<string, string > features;
	Rect position;

	string sql = "select * from imagePatch where imagePatchId ='" + imagePatchId + "'";
	//ִ�в�ѯ
	sqlite3_stmt *pstmt;
	const char   *error = 0;
	//if (sqlite3_prepare(SQLiteHelper::getSqlite3(), sql.c_str(), sql.size(), &pstmt, &error) == SQLITE_OK) {
	if (sqlite3_prepare(SQLiteHelper::sqlite_db_, sql.c_str(), sql.size(), &pstmt, &error) == SQLITE_OK) {
		while (1)
		{
			int ret = sqlite3_step(pstmt);
			if (ret != SQLITE_ROW)
				break;
			//imagePatchId = ((char*)sqlite3_column_text(pstmt, 0));
			originalImageId = ((char*)sqlite3_column_text(pstmt, 1));
			superImagePatchId = ((char*)sqlite3_column_text(pstmt, 2));
			positionStr = ((char*)sqlite3_column_text(pstmt, 3));
			binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 4));
			originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 5));
			featuresStr = ((char*)sqlite3_column_text(pstmt, 6));
		}
	}
	sqlite3_finalize(pstmt);
	jsonString2Mat(binaryImagePatchBuffer, *binaryImagePatch);
	jsonString2Mat(originalImagePatchBuffer, *originalImagePatch);
	jsonString2Map(featuresStr, features);
	position = jsonString2Rect(positionStr);

	if (originalImageId.empty())
	{
		logDisplay->logDisplay("Error in reading image patch from database!");
	}
	OriginalImage* ori = new OriginalImage(originalImageId);
	pip = new ImagePatch(imagePatchId, ori, position, binaryImagePatch, originalImagePatch);

	return pip;

}

//superImagePatch(superImagePatchId varchar, binarySuperImagePatch blob, originalSuperImagePatch blob, features text)
SuperImagePatch* readSuperImagePatch(string superImagePatchId)
{
	SuperImagePatch* sip;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;
	string imagePatchIdList;

	Mat *binaryImagePatch = new Mat;
	Mat *originalImagePatch = new Mat;
	map<string, string> features;
	vector<string> patchIdList;

	string sql = "select * from superImagePatch where superImagePatchId = '" + superImagePatchId + "'";
	//ִ�в�ѯ
	sqlite3_stmt *pstmt;
	const char   *error = 0;
	//if (sqlite3_prepare(SQLiteHelper::getSqlite3(), sql.c_str(), sql.size(), &pstmt, &error) == SQLITE_OK) {
	if (sqlite3_prepare(SQLiteHelper::sqlite_db_, sql.c_str(), -1, &pstmt, &error) == SQLITE_OK) {
		while (1)
		{
			int ret = sqlite3_step(pstmt);
			if (ret != SQLITE_ROW)
				break;
			superImagePatchId = ((char*)sqlite3_column_text(pstmt, 0));
			binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 1));
			originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 2));
			featuresStr = ((char*)sqlite3_column_text(pstmt, 3));
			imagePatchIdList = ((char*)sqlite3_column_text(pstmt, 4));
		}
	}
	else
	{
		logDisplay->logDisplay("Error in reading a SuperImagePatch form database.");
	}
	sqlite3_finalize(pstmt);
	jsonString2Mat(binaryImagePatchBuffer, *binaryImagePatch);
	jsonString2Mat(originalImagePatchBuffer, *originalImagePatch);
	jsonString2Map(featuresStr, features);
	string pattern = ",";
	patchIdList = split(imagePatchIdList, pattern);
	sip = new SuperImagePatch(superImagePatchId, binaryImagePatch, originalImagePatch);
	sip->setFeatures(features);
	sip->setPatchIdList(patchIdList);
	return sip;
}

/*
read all superImagePatches in the database
*/
vector<Patch*> readAllSuperImagePatches()
{
	vector<Patch*> images;

	SuperImagePatch* sip;
	string superImagePatchId;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;
	string imagePatchIdList;

	map<string, string> features;
	vector<string> patchIdList;

	string sql = "select * from superImagePatch";
	//ִ�в�ѯ
	sqlite3_stmt *pstmt;
	const char   *error = 0;
	//if (sqlite3_prepare(SQLiteHelper::getSqlite3(), sql.c_str(), sql.size(), &pstmt, &error) == SQLITE_OK) {
	if (sqlite3_prepare(SQLiteHelper::sqlite_db_, sql.c_str(), -1, &pstmt, &error) == SQLITE_OK) {
		while (1)
		{
			int ret = sqlite3_step(pstmt);
			if (ret != SQLITE_ROW)
				break;
			superImagePatchId = ((char*)sqlite3_column_text(pstmt, 0));
			binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 1));
			originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 2));
			featuresStr = ((char*)sqlite3_column_text(pstmt, 3));
			imagePatchIdList = ((char*)sqlite3_column_text(pstmt, 4));

			Mat *binaryImagePatch = new Mat;
			Mat *originalImagePatch = new Mat;

			jsonString2Mat(binaryImagePatchBuffer, *binaryImagePatch);
			jsonString2Mat(originalImagePatchBuffer, *originalImagePatch);
			jsonString2Map(featuresStr, features);
			string pattern = ",";
			patchIdList = split(imagePatchIdList, pattern);
			sip = new SuperImagePatch(superImagePatchId, binaryImagePatch, originalImagePatch);
			sip->setFeatures(features);
			sip->setPatchIdList(patchIdList);
			images.push_back(sip);
		}
	}
	else
	{
		logDisplay->logDisplay("Error in reading AllSuperImagePatches form database.");
	}
	sqlite3_finalize(pstmt);
	
	return images;
}


/*
�������ݿ���superImagePatch������
*/
int countRowsInSuperImagePatch()
{
	int rows;
	string sql = "select count(*) from superImagePatch ";
	//ִ�в�ѯ
	char *errmsg = NULL;
	char** dbResult = NULL;
	int nRow, nColumn;
	//int result = sqlite3_get_table(SQLiteHelper::getSqlite3(), sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
	int result = sqlite3_get_table(SQLiteHelper::sqlite_db_, sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	//��ѯ�ɹ�
	int index = nColumn; //dbResult ǰ���һ���������ֶ�����count���� nColumn ������ʼ��������������

	string rowsStr = dbResult[1];// dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ�����涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ
	sqlite3_free_table(dbResult);//�ͷŲ�ѯ�ռ�
	rows = atoi(rowsStr.c_str());
	return rows;
}
/*
read superImagePatches from table superImagePatch from start to start+pageSize rows in the database
*/
vector<Patch*> readPartSuperImagePatches(int start, int pageSize)
{
	vector<Patch*> images;

	SuperImagePatch* sip;
	string superImagePatchId;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;
	string imagePatchIdList;

	map<string, string> features;
	vector<string> patchIdList;

	string sql = "select * from superImagePatch limit " + to_string(start) + ","+ to_string(pageSize) + ";";
	//ִ�в�ѯ
	sqlite3_stmt *pstmt;
	const char   *error = 0;
	//if (sqlite3_prepare(SQLiteHelper::getSqlite3(), sql.c_str(), sql.size(), &pstmt, &error) == SQLITE_OK) {
	if (sqlite3_prepare(SQLiteHelper::sqlite_db_, sql.c_str(), -1, &pstmt, &error) == SQLITE_OK) {
		while (1)
		{
			int ret = sqlite3_step(pstmt);
			if (ret != SQLITE_ROW)
				break;
			superImagePatchId = ((char*)sqlite3_column_text(pstmt, 0));
			binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 1));
			originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 2));
			featuresStr = ((char*)sqlite3_column_text(pstmt, 3));
			imagePatchIdList = ((char*)sqlite3_column_text(pstmt, 4));

			Mat *binaryImagePatch = new Mat;
			Mat *originalImagePatch = new Mat;

			jsonString2Mat(binaryImagePatchBuffer, *binaryImagePatch);
			jsonString2Mat(originalImagePatchBuffer, *originalImagePatch);
			jsonString2Map(featuresStr, features);
			string pattern = ",";
			patchIdList = split(imagePatchIdList, pattern);
			sip = new SuperImagePatch(superImagePatchId, binaryImagePatch, originalImagePatch);
			sip->setFeatures(features);
			sip->setPatchIdList(patchIdList);
			images.push_back(sip);
		}
	}
	else
	{
		logDisplay->logDisplay("Error in reading the specified number of SuperImagePatches form database.");
	}
	sqlite3_finalize(pstmt);

	return images;
}
/*
����superImagePatch����superImagePatch�������vector<string> patchIdList����ImagePatch���superImagePatchId
*/
int updateImagePatchTable(SuperImagePatch & sip)
{
	string superImagePatchId = sip.getSuperImagePatchId();
	string imagePatchId = "";
	vector<string> patchIdList = sip.getPatchIdList();
	for (int i = 0; i < patchIdList.size(); i++)
	{
		imagePatchId = patchIdList[i];
		//����superImagePatchId
		string sql = "update imagePatch set superImagePatchId ='" + superImagePatchId + "' where imagePatchId = '" + imagePatchId + "';" ; 
		int res =  SQLiteHelper::Update(sql.c_str());
		if (res == -1){
			logDisplay->logDisplay("Error in update imagePatch set superImagePatchId");
			return -1;
		}
	}

	//test read
	//ImagePatch *temp = readImagePatch(imagePatchId);

	return 0;
}