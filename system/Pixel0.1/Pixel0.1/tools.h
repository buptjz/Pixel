//
//  tools.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__tools__
#define __Xcode_Pixel_Proj__tools__

#include <opencv.hpp>
#include <string>
#include <time.h>
#include "patch.h"
#include "misc.h"

//convert connected component to color image (for showing while debug)
void connected_component2color_image(const Mat &cc, Mat ret_color_image);

//generate random rgb color
rgb random_rgb();

//cout Mat info
void tool_print_mat_info(Mat);

//show patch tool function
void tool_show_patch(Patch *image, string name);
void tool_show_mat(Mat mat,string name);

//generate an unique id by current timestamp

string super_patch_id_from_timestamp();

template<class base_type,class child_type>
vector<base_type*> convert_verctor(vector<child_type*> src)
{
	vector<base_type*> ret;
	for(size_t i = 0;i < src.size(); ++i)
		ret.push_back(src[i]);
	return ret;
}

//read an image and change its depth
Mat imread_and_preprocess(const string& filename);


//split string
std::vector<std::string> split(std::string str, std::string pattern);

//draw patch in originalImage
void drawPatch(Mat& image, const Rect &position);
#endif /* defined(__Xcode_Pixel_Proj__tools__) */
