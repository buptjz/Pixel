//
//  tools.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__tools__
#define __Xcode_Pixel_Proj__tools__

#include <stdio.h>
#include <highgui.h>
#include <opencv.hpp>
#include <string>
#include "patch.h"

//show patch tool function
void tool_show_patch(Patch *image, string name);
void tool_show_mat(Mat mat,string name);

#endif /* defined(__Xcode_Pixel_Proj__tools__) */
