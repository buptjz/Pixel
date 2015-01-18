#include "superImagePatch.h"
#include "imagePatch.h"
#include "jsonHelper.h"
#include "sqlliteHelper.h"
#include "logDisplay.h"
extern LogDisplay* logDisplay;
/*
����СͼԪ���бȽϣ����ر�ʾ���ƶȵ�һ����
����һ��ͼԪ��SuperImagePatch�������뵱ǰͼԪ���бȽϣ���������ͼԪ�����ƶ�
Patch����ΪSuperImagePatch�ĸ��࣬ʵ�ʴ���SuperImagePatch
featureTypeΪ��ͼԪ�Ա�ʱʹ�õ�����������Ƕ�����������»��߸�����
��ʹ����sift��harris���������ʾΪsift_harris

double SuperImagePatch::patchCompareWith(Patch *pImagePatch, string featureType)
{
	//
	return 0;
}
*/
//����ͼԪ�������ݿ���
void SuperImagePatch::savePatch() const{
	std::stringstream str_sql;
	const string superImagePatchIdStr = superImagePatchId;
	string binarySuperImagePatchBuffer;
	mat2jsonString(*((Mat*)getBinaryImagePatch()), binarySuperImagePatchBuffer);
	string originalSuperImagePatchBuffer;
	mat2jsonString(*((Mat*)getOriginalImagePatch()), originalSuperImagePatchBuffer);
	string featuresStr;
    map<string, string> tmp = getFeatures();
	map2JsonString(tmp, featuresStr);
	//��ͼԪid�б��á�,���ָ�
	string imagePatchIdList = "";
	vector<string> patchIdList = getPatchIdList();
	for (int i = 0; i < patchIdList.size(); i++)
	{
		imagePatchIdList = imagePatchIdList + patchIdList[i] + ",";
	}
	imagePatchIdList = imagePatchIdList.substr(0, imagePatchIdList.size() - 1);
	str_sql << "insert into superImagePatch (superImagePatchId, binarySuperImagePatch, originalSuperImagePatch, features, imagePatchIdList) values(";
	str_sql << "'"<<superImagePatchIdStr <<"'"<<  "," << "?" << "," << "?" << "," << "?";
	str_sql << ","<<"?"<<");";
	std::string str = str_sql.str();
	sqlite3_stmt * stat = NULL;  //Ԥ����ʹ�õ���һ������Ҫ�����ݽṹ
	//int result = sqlite3_prepare(SQLiteHelper::getSqlite3(), str.c_str(), -1, &stat, 0);  //Ԥ����
	int result = sqlite3_prepare(SQLiteHelper::sqlite_db_, str.c_str(), -1, &stat, 0);
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving superImagePatch, sql sentence error!");
		sqlite3_finalize(stat);
		return;
	}
	
	result = sqlite3_bind_blob(stat, 1, binarySuperImagePatchBuffer.c_str(), binarySuperImagePatchBuffer.size(), NULL);   //��blob����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving superImagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_blob(stat, 2, originalSuperImagePatchBuffer.c_str(), originalSuperImagePatchBuffer.size(), NULL);   //��blob����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving superImagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_text(stat, 3, featuresStr.c_str(), -1, NULL);           //��text����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving superImagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_bind_text(stat, 4, imagePatchIdList.c_str(), -1, NULL);           //��text����
	if (result != SQLITE_OK)
	{
		logDisplay->logDisplay("Error in saving superImagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	result = sqlite3_step(stat);                              //ִ��sql��䣬�����Ͱ����ݴ浽���ݿ�����
	if (result != SQLITE_DONE)
	{
		logDisplay->logDisplay("Error in saving superImagePatch!");
		sqlite3_finalize(stat);
		return;
	}
	sqlite3_finalize(stat);
}