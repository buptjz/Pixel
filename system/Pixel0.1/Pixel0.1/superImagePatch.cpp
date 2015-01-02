#include "superImagePatch.h"
#include "imagePatch.h"
#include "jsonHelper.h"
#include "sqlliteHelper.h"
/*
两个小图元进行比较，返回表示相似度的一个数
输入一个图元（SuperImagePatch）对象，与当前图元进行比较，返回两个图元的相似度
Patch这里为SuperImagePatch的父类，实际传入SuperImagePatch
featureType为两图元对比时使用的特征，如果是多个特征，用下划线隔开，
如使用了sift和harris特征，则表示为sift_harris

double SuperImagePatch::patchCompareWith(Patch *pImagePatch, string featureType)
{
	//
	return 0;
}
*/
//将超图元存入数据库中
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
	//子图元id列表，用“,”分隔
	string imagePatchIdList = "";
	vector<string> patchIdList = getPatchIdList();
	for (int i = 0; i < patchIdList.size(); i++)
	{
		imagePatchIdList = imagePatchIdList + patchIdList[i] + ",";
	}
	str_sql << "insert into superImagePatch values(";
	str_sql << "'"<<superImagePatchIdStr <<"'"<<  "," << "?" << "," << "?" << "," << "?";
	str_sql << ","<<"?"<<");";
	std::string str = str_sql.str();
	sqlite3_stmt * stat = NULL;  //预编译使用到的一个很重要的数据结构
	//int result = sqlite3_prepare(SQLiteHelper::getSqlite3(), str.c_str(), -1, &stat, 0);  //预编译
	int result = sqlite3_prepare(SQLiteHelper::sqlite_db_, str.c_str(), -1, &stat, 0);
	result = sqlite3_bind_blob(stat, 1, binarySuperImagePatchBuffer.c_str(), binarySuperImagePatchBuffer.size(), NULL);   //绑定blob类型
	result = sqlite3_bind_blob(stat, 2, originalSuperImagePatchBuffer.c_str(), originalSuperImagePatchBuffer.size(), NULL);   //绑定blob类型
	result = sqlite3_bind_text(stat, 3, featuresStr.c_str(), -1, NULL);           //绑定text类型
	result = sqlite3_bind_text(stat, 4, imagePatchIdList.c_str(), -1, NULL);           //绑定text类型
	result = sqlite3_step(stat);                              //执行sql语句，这样就把数据存到数据库里了
	if (result != SQLITE_DONE)
	{
		printf("insert into blob value failure!");
	}
	sqlite3_finalize(stat);
}