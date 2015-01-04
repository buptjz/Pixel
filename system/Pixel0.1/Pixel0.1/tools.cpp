//
//  tools.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include "tools.h"
#include "params.h"
#include <time.h>
#include <ctime>

//cout Mat info
void tool_print_mat_info(Mat M){
    cout << "---------- Mat Info ----------" << endl;
    cout << "[Cols ] " << M.cols << endl;
    cout << "[Rows ] " << M.rows << endl;
    cout << "[eSize] " << M.elemSize() << endl;
    cout << "[Chann] " << M.channels() << endl;
    cout << "[Depth] " << M.depth() << endl;
    cout << "[Conti] " << M.isContinuous() << endl;
    cout << "[lengt] " << M.dataend - M.datastart << endl;
    cout << "------------------------------" << endl;

}


void tool_show_patch(Patch *image, string name){
    cv::namedWindow(name);
    cv::imshow(name, *(image->getOriginalImagePatch()));
    cv::waitKey(0);
}

void tool_show_mat(Mat mat,string name){
    cv::namedWindow(name);
    cv::imshow(name, mat);
    cv::waitKey(0);
}


string super_patch_id_from_timestamp(){
    static long long unique_patch_id = 0;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer,80,"%Y%m%d%I%M%S_",timeinfo);
    string str(buffer);
    str += to_string(unique_patch_id);
    unique_patch_id++;

    return str;
}

string getTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d %I:%M:%S", timeinfo);
	string str(buffer);
	return str;
}

Mat imread_and_preprocess(const string& filename)
{
	Mat tmp = imread(filename);
	if(tmp.data == NULL)
		return tmp;
	tmp.convertTo(tmp,Params::color_image_type);
	return tmp;
}

//字符串分割函数
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	//str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

void drawPatch(Mat& image, const Rect &position)
{
	//Mat image_clone = image.clone();
	int channels = image.channels();

	int x = position.x;
	int y = position.y;
	int height = position.height;
	int width = position.width;

	//rectangle(image, Point(x, y), Point(x + height, y + width), Scalar(0, 255, 255), 1, 8);
	rectangle(image, Point(x, y), Point(x+ width, y + height), Scalar(0, 0, 255), 3, 8);
	namedWindow("image", WINDOW_KEEPRATIO);
	imshow("image", image);

	waitKey(0);
}
