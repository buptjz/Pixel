//
//  params.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/18.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//
#include "params.h"
#include <opencv2/imgproc.hpp>
const string Params::SIFT = "SIFT";
const string Params::SHAPE_CONTEXT = "SHAPE_CONTEXT";
const string Params::SURF = "SURF";
const string Params::MORPH_BASIC = "MORPH_BASIC";
const string Params::EGBIS = "EGBIS";

//params for images
int Params::color_image_type = CV_8UC3;
int Params::color_image_channels = 3;
int Params::grey_image_type = CV_8UC1;
int Params::grey_image_channels = 1;
int Params::connect_map_type = CV_16UC1;

//segment
float Params::patch_pixel_min = 0.01;
float Params::patch_pixel_max = 0.85;
float Params::egbis_sigma = 0.5;
float Params::egbis_c = 500;
int Params::egbis_min_size = 20;

//params for match
int Params::shape_context_sample_point_num = 100;
float Params::shape_context_bending_weight = 0;

float Params::shape_context_match_weight = 1;
float Params::shape_context_appearance_weight = 0;
bool Params::shape_context_use_rotation = false;
int Params::surf_descriptor_min = 3;

//shape context compare
double Params::shape_context_compare_1_thres = 0.15;
double Params::shape_context_compare_2_thres = 0.15;
double Params::surf_compare_1_thres = 0.7;
double Params::surf_compare_2_thres = 0.7;

int Params::surf_dimensions = 64;
double Params::surf_min_ratio = 1.0f / 1.5f;


string Params::featureType = SHAPE_CONTEXT;//featureType used 
string Params::segment_type = Params::MORPH_BASIC;
size_t Params::top_k = 5;//return the top_k simplar superImagePatches
