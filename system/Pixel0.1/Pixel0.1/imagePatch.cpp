#include "imagePatch.h"
#include "originalImage.h"
#include "superImagePatch.h"
#include "jsonHelper.h"
#include "patch.h"
#include<map>
#include<vector>
using namespace cv;
using namespace std;
/*
两个小图元进行比较，返回表示相似度的一个数
输入一个图元（ImagePatch）对象，与当前图元进行比较，返回两个图元的相似度
Patch这里为ImagePatch的父类，实际传入ImagePatch
featureType为两图元对比时使用的特征，如果是多个特征，用下划线隔开，
如使用了sift和harris特征，则表示为sift_harris

double ImagePatch::patchCompareWith(Patch *pImagePatch, string featureType){
	//
	return 0;
}
*/

//将小图元存入数据库中
void ImagePatch::savePatch() const{
	std::stringstream str_sql;
	const string originalImageIdsStr = originalImage->getOriginalImageId();
	const string superImagePatchId = superImagePatch->getSuperImagePatchId();
	string positionStr = rect2JsonString(position);
	string binaryImagePatchBuffer;
	mat2jsonString(*((Mat*)getBinaryImagePatch()), binaryImagePatchBuffer);
	string originalImagePatchBuffer;
	mat2jsonString(*((Mat*)getOriginalImagePatch()), originalImagePatchBuffer);
	string featuresStr;
    
    map<string, vector<double> > tmp = getFeatures();
	map2JsonString(tmp, featuresStr);

	str_sql << "insert into imagePatch values(";
	str_sql << imagePatchId << "," << originalImageIdsStr << "," << superImagePatch << ",";
	str_sql << positionStr<<","<<"?"<<","<<"?"<<","<<"?";
	str_sql << ");";
	std::string str = str_sql.str();
	sqlite3_stmt * stat = NULL;  //预编译使用到的一个很重要的数据结构
	//int result = sqlite3_prepare(SQLiteHelper::getSqlite3(), str.c_str(), -1, &stat, 0);  //预编译
	int result = sqlite3_prepare(SQLiteHelper::sqlite_db_, str.c_str(), -1, &stat, 0);
	
	result = sqlite3_bind_blob(stat, 1, binaryImagePatchBuffer.c_str(), binaryImagePatchBuffer.size(), NULL);   //绑定blob类型
	result = sqlite3_bind_blob(stat, 2, originalImagePatchBuffer.c_str(), originalImagePatchBuffer.size(), NULL);   //绑定blob类型
	result = sqlite3_bind_text(stat, 3,featuresStr.c_str(), -1, NULL);           //绑定表的第一个字段，这里为text类型
	result = sqlite3_step(stat);                              //执行sql语句，这样就把数据存到数据库里了
	if (result != SQLITE_DONE)
	{
		printf("insert into blob value failure!");
	}
	//sql_lite_helper.Insert(str.c_str());
}


