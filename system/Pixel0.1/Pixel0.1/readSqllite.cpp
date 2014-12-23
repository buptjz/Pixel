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
	//��ѯ�ɹ�
	int index = nColumn; //dbResult ǰ���һ���������ֶ����ƣ��� nColumn ������ʼ��������������

	string path = dbResult[1];// dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ�����涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ
	Mat pOImage = imread(path.c_str(), -1);
	
	poi = new OriginalImage(originalImageId, path, &pOImage);

	sqlite3_free_table(dbResult);//�ͷŲ�ѯ�ռ�
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
	//�ر����ݿ�
	/*
	char *errmsg = NULL;
	char** dbResult = NULL;
	int nRow, nColumn;
	int result = sqlite3_get_table(sql_lite_helper.getSqlite3(), sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	//��ѯ�ɹ�
	int index = nColumn; //dbResult ǰ���һ���������ֶ����ƣ��� nColumn ������ʼ��������������
	string originalImageId = dbResult[index++];
	string superImagePatchId = dbResult[index++];
	string positionStr = dbResult[index++];
	string binaryImagePatchBuffer = dbResult[index++];
	string originalImagePatchBuffer = dbResult[index++];
	string featuresStr = dbResult[index++];
	

	sqlite3_free_table(dbResult);//�ͷŲ�ѯ�ռ�
	*/


	return pip;

}