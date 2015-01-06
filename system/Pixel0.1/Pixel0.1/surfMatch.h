//
//  surfMatch.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/21.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__surfMatch__
#define __Xcode_Pixel_Proj__surfMatch__

#include "imagePatch.h"

/*--------------------------------------
 Surf Interfaces: Supported by JZ
 match two patches using surf algorithm
 --------------------------------------*/

/*
 * Get surf descriptors from an image mat
 * img: input image
 * ret_descriptors : surf descriptors (each descriptor a row, 64 cols)
 */
void generate_surf_descriptors(const Mat &img, Mat &ret_descriptors);

/*
 * Return matching score by surf algorithm with two Images Mats
 * img1 : input image 1
 * img2 : input image 2
 * return double as the matching score
 * matching score is s, 0 <= s <=1, s = number of matching / number of desp1
 */
double surf_match_score_with_mat(const Mat &img1,const Mat &img2);

/*
 * Return matching score by surf algorithm with two descriptors' vectors
 * desp1 : image 1 descriptors
 * desp2 : iamge 2 descriptors
 * return double as the matching score
 * matching score is s, 0 <= s <=1, s = number of matching / number of desp1
 */
double surf_match_score_with_descriptor(const Mat &desp1, const Mat &desp2);

//test function
void test_surf_match_func();

#endif /* defined(__Xcode_Pixel_Proj__surfMatch__) */
