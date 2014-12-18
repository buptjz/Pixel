#include "imagePatch.h"
#include "originalImage.h"
#include "superImagePatch.h"
using namespace cv;
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
void ImagePatch::savePatch(SQLiteHelper &sql_lite_helper) const{
	std::stringstream str_sql;
	const string originalImageId = originalImage->getOriginalImageId();
	const string superImagePatchId = superImagePatch->getSuperImagePatchId();
	string position;
	Mat *binarySuperBuffer;
	Mat *originalSuperBuffer;
	string features;
	str_sql << "insert into imagePatch values(";
	str_sql << imagePatchId << "," << originalImageId << ","<<superImagePatch<<",";
	str_sql << "";
	str_sql << ");";
	std::string str = str_sql.str();
	sql_lite_helper.Insert(str.c_str());
}
