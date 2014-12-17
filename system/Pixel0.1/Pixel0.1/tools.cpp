//
//  tools.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#include "tools.h"

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
