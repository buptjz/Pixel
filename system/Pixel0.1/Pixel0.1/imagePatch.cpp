#include "imagePatch.h"
#include "originalImage.h"
#include "superImagePatch.h"
#include "jsonHelper.h"
#include "patch.h"
#include<map>
#include<vector>
#include "logDisplay.h"
extern LogDisplay* logDisplay;
using namespace cv;
using namespace std;
/*
����СͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����
����һ��ͼԪ��ImagePatch�������뵱ǰͼԪ���бȽϣ���������ͼԪ�����ƶ�
Patch����ΪImagePatch�ĸ��࣬ʵ�ʴ���ImagePatch
featureTypeΪ��ͼԪ�Ա�ʱʹ�õ�����������Ƕ�����������»��߸�����
��ʹ����sift��harris���������ʾΪsift_harris

double ImagePatch::patchCompareWith(Patch *pImagePatch, string featureType){
	//
	return 0;
}
*/

//��СͼԪ�������ݿ���
void ImagePatch::savePatch() const{
	std::stringstream str_sql;
	const string originalImageIdsStr = originalImage->getOriginalImageId();
	const string superImagePatchId = "";
 	string positionStr = rect2JsonString(position);
	string binaryImagePatchBuffer;
	mat2jsonString(*((Mat*)getBinaryImagePatch()), binaryImagePatchBuffer);
	string originalImagePatchBuffer;
	mat2jsonString(*((Mat*)getOriginalImagePatch()), originalImagePatchBuffer);
	string featuresStr;
    
    map<string, string > tmp = getFeatures();
	map2JsonString(tmp, featuresStr);

	str_sql << "insert into imagePatch values('";
	str_sql << imagePatchId << "','" << originalImageIdsStr << "','" << superImagePatchId<< "','";
	str_sql << positionStr<<"',"<<"?"<<","<<"?"<<","<<"?";
	str_sql << ");";
	std::string str = str_sql.str();
	sqlite3_stmt * stat = NULL;  //Ԥ����ʹ�õ���һ������Ҫ�����ݽṹ
	//int result = sqlite3_prepare(SQLiteHelper::getSqlite3(), str.c_str(), -1, &stat, 0);  //Ԥ����
	int result = sqlite3_prepare(SQLiteHelper::sqlite_db_, str.c_str(), -1, &stat, 0);
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving imagePatch, sql sentence error!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_blob(stat, 1, binaryImagePatchBuffer.c_str(), binaryImagePatchBuffer.size(), NULL);   //��blob����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving imagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_blob(stat, 2, originalImagePatchBuffer.c_str(), originalImagePatchBuffer.size(), NULL);   //��blob����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving imagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_text(stat, 3,featuresStr.c_str(), -1, NULL);           //�󶨱�ĵ�һ���ֶΣ�����Ϊtext����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving imagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_step(stat);                              //ִ��sql��䣬�����Ͱ����ݴ浽���ݿ�����
	if (result != SQLITE_DONE)
	{
		logDisplay->logDisplay("Error in saving imagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	sqlite3_finalize(stat);
	//sql_lite_helper.Insert(str.c_str());
}


