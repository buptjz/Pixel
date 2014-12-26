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
using namespace cv;

OriginalImage* readOriginalImage(string originalImageId)
{
	OriginalImage* poi;
	string sql = "select path from originalImage where originalImageId = " + originalImageId;
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
	string superImagePatchI;
	string positionStr;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;

	Mat *binaryImagePatch = new Mat;
	Mat *originalImagePatch = new Mat;
	map<string, vector<double> > features;
	Rect position;

	string sql = "select * from imagePatch where imagePatchId =" + imagePatchId;
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
			string originalImageId((char*)sqlite3_column_text(pstmt, 0));
			string superImagePatchI((char*)sqlite3_column_text(pstmt, 1));
			string positionStr = ((char*)sqlite3_column_text(pstmt, 2));
			string binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 3));
			string originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 4));
			//int len = sqlite3_column_bytes(pstmt, 4);
			string featuresStr((char*)sqlite3_column_text(pstmt, 5));
		}
	}
	sqlite3_finalize(pstmt);
	jsonString2Mat(binaryImagePatchBuffer, *binaryImagePatch);
	jsonString2Mat(originalImagePatchBuffer, *originalImagePatch);
	jsonString2Map(featuresStr, features);
	position = jsonString2Rect(positionStr);
	OriginalImage* ori = new OriginalImage(originalImageId);
	pip = new ImagePatch(imagePatchId, ori, position, binaryImagePatch, originalImagePatch);
	//关闭数据库
	/*
	char *errmsg = NULL;
	char** dbResult = NULL;
	int nRow, nColumn;
	int result = sqlite3_get_table(sql_lite_helper.getSqlite3(), sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	//查询成功
	int index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
	string originalImageId = dbResult[index++];
	string superImagePatchId = dbResult[index++];
	string positionStr = dbResult[index++];
	string binaryImagePatchBuffer = dbResult[index++];
	string originalImagePatchBuffer = dbResult[index++];
	string featuresStr = dbResult[index++];
	

	sqlite3_free_table(dbResult);//释放查询空间
	*/


	return pip;

}
//superImagePatch(superImagePatchId varchar, binarySuperImagePatch blob, originalSuperImagePatch blob, features text)
SuperImagePatch* readSuperImagePatch(string superImagePatchId)
{
	SuperImagePatch* sip;
	string binaryImagePatchBuffer;
	string originalImagePatchBuffer;
	string featuresStr;

	Mat *binaryImagePatch = new Mat;
	Mat *originalImagePatch = new Mat;
	map<string, vector<double> > features;

	string sql = "select * from superImagePatch where superImagePatchId =" + superImagePatchId;
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
			string superImagePatchI((char*)sqlite3_column_text(pstmt, 0));
			string binaryImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 1));
			string originalImagePatchBuffer = ((char*)sqlite3_column_blob(pstmt, 2));
			string featuresStr((char*)sqlite3_column_text(pstmt, 3));
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
	sip = new SuperImagePatch(superImagePatchId, binaryImagePatch, originalImagePatch);
	//关闭数据库
	/*
	char *errmsg = NULL;
	char** dbResult = NULL;
	int nRow, nColumn;
	int result = sqlite3_get_table(sql_lite_helper.getSqlite3(), sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	//查询成功
	int index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
	string originalImageId = dbResult[index++];
	string superImagePatchId = dbResult[index++];
	string positionStr = dbResult[index++];
	string binaryImagePatchBuffer = dbResult[index++];
	string originalImagePatchBuffer = dbResult[index++];
	string featuresStr = dbResult[index++];
	sqlite3_free_table(dbResult);//释放查询空间
	*/

	return sip;

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
		string sql = "update imagePatch set superImagePatchId =" + superImagePatchId + "where imagePatchId = " + imagePatchId + ";" ; 
		int res =  SQLiteHelper::Update(sql.c_str());
		if (res == -1){
			return -1;
		}
	}


	return 0;
}