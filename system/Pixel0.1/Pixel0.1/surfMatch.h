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
 Surf Interfaces: Maintenance by JZ
 match two patches using surf algorithm
 */

//get surf descriptors from an image mat
void generate_surf_descriptors(const Mat &img, Mat &ret_descriptors);

//Return matching score by surf algorithm with two Images Mats
double surf_match_score_with_mat(const Mat &,const Mat&);

//Return matching score by surf algorithm with two descriptors' vectors
double surf_match_score_with_descriptor(const Mat&, const Mat&);

//test function
void test_surf_match_func();

#endif /* defined(__Xcode_Pixel_Proj__surfMatch__) */
