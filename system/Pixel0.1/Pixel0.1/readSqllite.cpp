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
	//查询成功
	int index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据

	string path = dbResult[1];// dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
	Mat pOImage = imread(path.c_str(), -1);
	
	poi = new OriginalImage(originalImageId, path, &pOImage);

	sqlite3_free_table(dbResult);//释放查询空间
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
	//执行查询
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
	//执行查询
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
		cout << "error in reading SuperImagePatch form database" << endl;
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
	//执行查询
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
		cout << "error in reading SuperImagePatch form database" << endl;
	}
	sqlite3_finalize(pstmt);
	
	return images;
}


/*
read number of k superImagePatches in the database
*/
vector<Patch*> readAllSuperImagePatches(int k)
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

	string sql = "select * from superImagePatch ";
	//执行查询
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
		cout << "error in reading SuperImagePatch form database" << endl;
	}
	sqlite3_finalize(pstmt);

	return images;
}
/*
生成superImagePatch后，由superImagePatch对象里的vector<string> patchIdList更新ImagePatch里的superImagePatchId
*/
int updateImagePatchTable(SuperImagePatch & sip)
{
	string superImagePatchId = sip.getSuperImagePatchId();
	string imagePatchId = "";
	vector<string> patchIdList = sip.getPatchIdList();
	for (int i = 0; i < patchIdList.size(); i++)
	{
		imagePatchId = patchIdList[i];
		//更新superImagePatchId
		string sql = "update imagePatch set superImagePatchId ='" + superImagePatchId + "' where imagePatchId = '" + imagePatchId + "';" ; 
		int res =  SQLiteHelper::Update(sql.c_str());
		if (res == -1){
			return -1;
		}
	}

	//test read
	//ImagePatch *temp = readImagePatch(imagePatchId);

	return 0;
}