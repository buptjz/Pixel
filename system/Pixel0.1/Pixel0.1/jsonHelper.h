#ifndef JSONHELPER_H
#define JSONHELPER_H
#include "json/json.h"
#include <map>
#include <cstring>
#include<iostream>
#include <memory.h>
#include <exception>
#include <string.h>
#include<vector>
#include<stdio.h>
#include "cv.h"
using namespace cv;
using namespace std;
//map类型转换为json字符串
int map2JsonString(map<string, vector<double> > m, string &jsonString);

//json字符串转换为map
int jsonString2Map(string &jsonString, map<string, vector<double> > m);

//Mat类型序列化为json字符串
int mat2jsonString(const Mat&  M, string &jsonString);


//json字符串序列化为Mat
int jsonString2Mat(string &jsonString, Mat& m);

#endif