#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <map>
#include <cstring>
#include<iostream>
#include <string.h>
#include<vector>
#include<stdio.h>
#include "cv.h"
using namespace cv;
using namespace std;
//map����ת��Ϊjson�ַ���
int map2JsonString(map<string, vector<double> > &m, string &jsonString);

//json�ַ���ת��Ϊmap
int jsonString2Map(string &jsonString, map<string, vector<double> > &m);

//Mat�������л�Ϊjson�ַ���
int mat2jsonString(const Mat&  M, string &jsonString);


//json�ַ������л�ΪMat
int jsonString2Mat(string &jsonString, Mat& m);

string rect2JsonString(const Rect &rect);
Rect jsonString2Rect(string &str);
#endif