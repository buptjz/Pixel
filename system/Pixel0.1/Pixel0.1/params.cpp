//
//  params.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/18.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//
#include "params.h"
#include <opencv2/imgproc.hpp>
#include <map>
const string Params::SIFT = "SIFT";
const string Params::SHAPE_CONTEXT = "SHAPE_CONTEXT";
const string Params::SURF = "SURF";
const string Params::MORPH_BASIC = "MORPH_BASIC";
const string Params::EGBIS = "EGBIS";

map<string, pair<string, void*> > Params::__attr__;

//params for images
int Params::color_image_type = CV_8UC3;
int Params::color_image_channels = 3;
int Params::grey_image_type = CV_8UC1;
int Params::grey_image_channels = 1;
int Params::connect_map_type = CV_16UC1;

//segment
double Params::pixel_rat_min = 0.00005;
int Params::retry_max = 10;
float Params::segment_expect_upboard = 5.0;
float Params::segment_expect_lowboard = 0.3;
int Params::segment_expect = 0;
float Params::segment_step = 0.2;
float Params::patch_pixel_min = 0.01;
float Params::patch_pixel_max = 0.85;

float Params::morph_min = 0.4;
float Params::egbis_sigma = 0.5;
float Params::egbis_c = 5000;
int Params::egbis_min_size = 20;

//params for match
int Params::shape_context_sample_point_num = 100;
float Params::shape_context_bending_weight = 0;

float Params::shape_context_match_weight = 1;
float Params::shape_context_appearance_weight = 0;
bool Params::shape_context_use_rotation = false;
int Params::surf_descriptor_min = 3;

//shape context compare
double Params::shape_context_compare_1_thres = 0.2;
double Params::shape_context_compare_2_thres = 0.2;
double Params::surf_compare_1_thres = 0.4;
double Params::surf_compare_2_thres = 0.6;

int Params::surf_dimensions = 64;
double Params::surf_min_ratio = 1.0f / 1.5f;



string Params::featureType_for_one_image = SHAPE_CONTEXT;//featureType used 
string Params::featureType_for_batch_image = SHAPE_CONTEXT;
string Params::featureType_for_search = SHAPE_CONTEXT;
string Params::segment_type_for_one_image = Params::MORPH_BASIC;
string Params::segment_type_for_batch_image = Params::MORPH_BASIC;
int Params::top_k = 5;//return the top_k simplar superImagePatches

string Params::defaultPath = "ExternalImportImages";//the file in which users save an external image

void Params::push_attr()
{
	__attr__["color_image_type"] = make_pair("int", static_cast<void*>(&color_image_type));
	__attr__["color_image_channels"] = make_pair("int", static_cast<void*>(&color_image_channels));
	__attr__["grey_image_type"] = make_pair("int", static_cast<void*>(&grey_image_type));
	__attr__["grey_image_channels"] = make_pair("int", static_cast<void*>(&grey_image_channels));
	__attr__["connect_map_type"] = make_pair("int", static_cast<void*>(&connect_map_type));
	__attr__["retry_max"] = make_pair("int", static_cast<void*>(&retry_max));
	__attr__["segment_expect_upboard"] = make_pair("float", static_cast<void*>(&segment_expect_upboard));
	__attr__["segment_expect_lowboard"] = make_pair("float", static_cast<void*>(&segment_expect_lowboard));
	__attr__["segment_expect"] = make_pair("int", static_cast<void*>(&segment_expect));
	__attr__["segment_step"] = make_pair("float", static_cast<void*>(&segment_step));
	__attr__["patch_pixel_min"] = make_pair("float", static_cast<void*>(&patch_pixel_min));
	__attr__["patch_pixel_max"] = make_pair("float", static_cast<void*>(&patch_pixel_max));
	__attr__["morph_min"] = make_pair("float", static_cast<void*>(&morph_min));

	__attr__["egbis_sigma"] = make_pair("float", static_cast<void*>(&egbis_sigma));
	__attr__["egbis_c"] = make_pair("float", static_cast<void*>(&egbis_c));
	__attr__["egbis_min_size"] = make_pair("int", static_cast<void*>(&egbis_min_size));

	__attr__["shape_context_sample_point_num"] = make_pair("int", static_cast<void*>(&shape_context_sample_point_num));
	__attr__["shape_context_bending_weight"] = make_pair("float", static_cast<void*>(&shape_context_bending_weight));
	__attr__["shape_context_match_weight"] = make_pair("float", static_cast<void*>(&shape_context_match_weight));
	__attr__["shape_context_appearance_weight"] = make_pair("float", static_cast<void*>(&shape_context_appearance_weight));
	__attr__["shape_context_use_rotation"] = make_pair("bool", static_cast<void*>(&shape_context_use_rotation));
	__attr__["surf_descriptor_min"] = make_pair("int", static_cast<void*>(&surf_descriptor_min));

	__attr__["shape_context_compare_1_thres"] = make_pair("double", static_cast<void*>(&shape_context_compare_1_thres));
	__attr__["shape_context_compare_2_thres"] = make_pair("double", static_cast<void*>(&shape_context_compare_2_thres));
	__attr__["surf_compare_1_thres"] = make_pair("double", static_cast<void*>(&surf_compare_1_thres));
	__attr__["surf_compare_2_thres"] = make_pair("double", static_cast<void*>(&surf_compare_2_thres));
	__attr__["surf_dimensions"] = make_pair("int", static_cast<void*>(&surf_dimensions));
	__attr__["surf_min_ratio"] = make_pair("double", static_cast<void*>(&surf_min_ratio));
	__attr__["featureType_for_one_image"] = make_pair("string", static_cast<void*>(&featureType_for_one_image));
	__attr__["featureType_for_batch_image"] = make_pair("string", static_cast<void*>(&featureType_for_batch_image));
	__attr__["featureType_for_search"] = make_pair("string", static_cast<void*>(&featureType_for_search));
	__attr__["segment_type_for_one_image"] = make_pair("string", static_cast<void*>(&segment_type_for_one_image));
	__attr__["segment_type_for_batch_image"] = make_pair("string", static_cast<void*>(&segment_type_for_batch_image));
	__attr__["top_k"] = make_pair("int", static_cast<void*>(&top_k));
	__attr__["pixel_rat_min"] = make_pair("double", static_cast<void*>(&pixel_rat_min));
	__attr__["defaultPath"] = make_pair("string", static_cast<void*>(&defaultPath));
}