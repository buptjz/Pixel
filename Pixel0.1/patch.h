#ifndef PATCH_H
#define PATCH_H

#include<string.h>
#include<iostream>
#include<vector>
using namespace std;
//ͼԪ���࣬СͼԪ�ͳ�ͼԪ���еĻ�������
class Patch{
	/*�͵�ǰͼԪ���бȽ�
	*���룺���Ƚϵ�ͼԪ���Ƚ�ʱʹ�õ���������
	*�������ͼԪ�ʹ��Ƚϵ�ͼԪ�����ƶ�
	*/
	virtual double patchCompareWith(Patch *pPatch, vector<string> featureType) = 0;
	//��СͼԪ�������ݿ���
	virtual void savePatch() = 0;
};


#endif