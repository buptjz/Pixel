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
//map类型转换为json字符串
int map2JsonString(const map<string, string> &m, string &jsonString);

//json字符串转换为map
int jsonString2Map(const string& jsonString, map<string, string > &m);

//Mat类型序列化为json字符串
int mat2jsonString(const Mat&  M, string &jsonString);


//json字符串序列化为Mat
int jsonString2Mat(const string &jsonString, Mat& M);

string rect2JsonString(const Rect &rect);
Rect jsonString2Rect(string &str);
#endif