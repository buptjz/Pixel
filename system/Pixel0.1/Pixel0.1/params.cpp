//
//  params.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/18.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//


#include "params.h"
const string Params::SIFT = "SIFT";
const string Params::SHAPE_CONTEXT = "SHAPE_CONTEXT";

//params for match
int Params::shape_context_sample_point_num = 100;
float Params::shape_context_bending_weight = 0;
float Params::shape_context_match_weight = 1;
float Params::shape_context_appearance_weight = 0;
bool Params::shape_context_use_rotation = false;

//shape context compare
double Params::shape_context_compare_1_thres = 0.1;
double Params::shape_context_compare_2_thres = 2.0;