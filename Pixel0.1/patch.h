#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<vector>
using namespace std;
//图元块类，小图元和超图元共有的基本方法
class Patch{
	/*和当前图元进行比较
	*输入：待比较的图元，比较时使用的特征种类
	*输出：本图元和待比较的图元的相似度
	*/
	virtual double patchCompareWith(Patch *pPatch, vector<string> featureType) = 0;
	//将小图元存入数据库中
	virtual void savePatch() = 0;
};


#endif