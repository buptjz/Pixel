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
int map2JsonString(const map<string, string> &m, string &jsonString);

//json�ַ���ת��Ϊmap
int jsonString2Map(const string& jsonString, map<string, string > &m);

//Mat�������л�Ϊjson�ַ���
int mat2jsonString(const Mat&  M, string &jsonString);


//json�ַ������л�ΪMat
int jsonString2Mat(const string &jsonString, Mat& M);

string rect2JsonString(const Rect &rect);
Rect jsonString2Rect(string &str);
#endif