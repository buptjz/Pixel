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
#include <ctime>

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

Mat imread_and_preprocess(const string& filename)
{
	Mat tmp = imread(filename);
	if(tmp.data == NULL)
		return tmp;
	tmp.convertTo(tmp,Params::color_image_type);
	return tmp;
}