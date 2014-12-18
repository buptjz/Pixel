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

string rect2JsonString(const Rect &rect)
{
	map<string, vector<double> > m;
	vector<double> v;
	double x = (double)rect.x;
	double y = (double)rect.y;
	double w = (double)rect.width;
	double h = (double)rect.height;
	v.push_back(x);
	v.push_back(y);
	v.push_back(w);
	v.push_back(h);
	m["position"] = v;
	string res;
	map2JsonString(m, res);
	return res;
}

//��СͼԪ�������ݿ���
void ImagePatch::savePatch(SQLiteHelper &sql_lite_helper) const{
	std::stringstream str_sql;
	const string originalImageId = originalImage->getOriginalImageId();
	const string superImagePatchId = superImagePatch->getSuperImagePatchId();
	string positionStr = rect2JsonString(position);
	string binarySuperBuffer;
	mat2jsonString(*((Mat*)getBinaryImagePatch()), binarySuperBuffer);
	string originalSuperBuffer;
	mat2jsonString(*((Mat*)getOriginalImagePatch()), originalSuperBuffer);
	string featuresStr;
	map2JsonString((map<string,vector<double> >)getFeatures(), featuresStr);
	str_sql << "insert into imagePatch values(";
	str_sql << imagePatchId << "," << originalImageId << ","<<superImagePatch<<",";
	str_sql << positionStr<<","<<binarySuperBuffer<<","<<originalSuperBuffer<<","<<featuresStr;
	str_sql << ");";
	std::string str = str_sql.str();
	sql_lite_helper.Insert(str.c_str());
}


