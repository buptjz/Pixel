//
//  surfMatch.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/21.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__surfMatch__
#define __Xcode_Pixel_Proj__surfMatch__

#include <stdio.h>
#include "imagePatch.h"

/*
 match two patches using surf algorithm, return the matching score
ranges [0,1] , the bigger, the better
 */
double surf_match_score(const ImagePatch &ip1, const ImagePatch &ip2);

int surf_match_func(const Mat &,const Mat &);
void test_surf_match_func();

#endif /* defined(__Xcode_Pixel_Proj__surfMatch__) */
