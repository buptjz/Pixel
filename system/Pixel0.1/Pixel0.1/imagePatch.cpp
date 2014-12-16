#include "imagePatch.h"
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
void ImagePatch::savePatch(){

}
