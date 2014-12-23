#include "superImagePatch.h"
#include "imagePatch.h"
#include "jsonHelper.h"
#include "sqlliteHelper.h"
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
//��СͼԪ�������ݿ���
void SuperImagePatch::savePatch() const{
	std::stringstream str_sql;
	const string superImagePatchIdStr = superImagePatchId;
	string binarySuperImagePatchBuffer;
	mat2jsonString(*((Mat*)getBinaryImagePatch()), binarySuperImagePatchBuffer);
	string originalSuperImagePatchBuffer;
	mat2jsonString(*((Mat*)getOriginalImagePatch()), originalSuperImagePatchBuffer);
	string featuresStr;
	map2JsonString((map<string, vector<double> >)getFeatures(), featuresStr);
	str_sql << "insert into imagePatch values(";
	str_sql << superImagePatchIdStr <<  "," << "?" << "," << "?" << "," << "?";
	str_sql << ");";
	std::string str = str_sql.str();
	sqlite3_stmt * stat = NULL;  //Ԥ����ʹ�õ���һ������Ҫ�����ݽṹ
	//int result = sqlite3_prepare(SQLiteHelper::getSqlite3(), str.c_str(), -1, &stat, 0);  //Ԥ����
	int result = sqlite3_prepare(SQLiteHelper::sqlite_db_, str.c_str(), -1, &stat, 0);
	result = sqlite3_bind_blob(stat, 1, binarySuperImagePatchBuffer.c_str(), binarySuperImagePatchBuffer.size(), NULL);   //��blob����
	result = sqlite3_bind_blob(stat, 2, originalSuperImagePatchBuffer.c_str(), originalSuperImagePatchBuffer.size(), NULL);   //��blob����
	result = sqlite3_bind_text(stat, 3, featuresStr.c_str(), -1, NULL);           //�󶨱�ĵ�һ���ֶΣ�����Ϊtext����
	result = sqlite3_step(stat);                              //ִ��sql��䣬�����Ͱ����ݴ浽���ݿ�����
	if (result != SQLITE_DONE)
	{
		printf("insert into blob value failure!");
	}
}