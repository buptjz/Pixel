//
//  image_convert.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/1.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__image_convert__
#define __Xcode_Pixel_Proj__image_convert__

#include <stdio.h>

#include <opencv2/core/core.hpp>
#include "image.h"
#include "misc.h"

image<rgb>* convertMatToNativeImage(const cv::Mat *input);

#endif /* defined(__Xcode_Pixel_Proj__image_convert__) */
