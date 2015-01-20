//
//  params.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/18.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//
#include "params.h"
#include <opencv2/opencv.hpp>
#include <map>
#include <math.h>
const string Params::SIFT = "SIFT";
const string Params::SHAPE_CONTEXT = "SHAPE_CONTEXT";
const string Params::SURF = "SURF";
const string Params::MORPH_BASIC = "MORPH_BASIC";
const string Params::EGBIS = "EGBIS";

map<string, pair<string, void*> > Params::__attr__;
//NOTE:attributes with 'non-user-set' means it should not be shown on GUI 
//params for images
int Params::color_image_type = CV_8UC3;//non-user-set
int Params::color_image_channels = 3;//non-user-set
int Params::grey_image_type = CV_8UC1;//non-user-set
int Params::grey_image_channels = 1;//non-user-set
int Params::connect_map_type = CV_16UC1;//non-user-set

//segment
double Params::pixel_rat_min = 0.1;
double Params::pixel_valid_thr = 0.2;//non-user-set
int Params::retry_max = 10;
float Params::segment_expect_upboard = 5.0;
float Params::segment_expect_lowboard = 0.3;
int Params::segment_expect = 0;
float Params::segment_step = 0.2;//non-user-set
int Params::patch_width_min = 10;

float Params::patch_pixel_min = 0.01;
float Params::patch_pixel_max = 0.85;

float Params::morph_min = 0.4;
double Params::morph_canny_low_thr = 50;
double Params::morph_canny_up_thr = 150;
int Params::morph_size = 5;
int Params::morph_scale = 3;
int Params::morph_smooth_ksize = 3;
bool Params::morph_fill_all = true;

float Params::egbis_sigma = 0.5;
float Params::egbis_c = 5000;
int Params::egbis_min_size = 20;

//params for match
int Params::shape_context_sample_point_num = 100;
float Params::shape_context_bending_weight = 0;

float Params::shape_context_match_weight = 1;
float Params::shape_context_appearance_weight = 0;
bool Params::shape_context_use_rotation = false;
int Params::shape_context_iterations = 2;
int Params::surf_descriptor_min = 3;

//shape context compare
double Params::shape_context_compare_1_thres = 0.2;
double Params::shape_context_compare_2_thres = 0.2;
double Params::surf_compare_1_thres = 0.45;
double Params::surf_compare_2_thres = 0.6;

int Params::surf_dimensions = 64;
double Params::surf_min_ratio = 1.0f / 1.5f;



string Params::featureType_for_one_image = SURF;//featureType used 
string Params::featureType_for_batch_image = SURF;
string Params::featureType_for_search = SURF;
string Params::segment_type_for_one_image = Params::EGBIS;
string Params::segment_type_for_batch_image = Params::EGBIS;
int Params::top_k = 5;//return the top_k simplar superImagePatches

string Params::defaultPath = "ExternalImportImages";//the file in which users save an external image
string Params::xmlFileName = "Params.xml";
int Params::pageSize = 30;

//generatrion
int Params::generation_height = 15;//number of generated mat in a col
int Params::generation_width = 18;//number of generated mat in a row
int Params::patch_scale = 50;//height of the patches used in generation

//rotate generation
double Params::angle = 0;//rotate angle(°)
double Params::rot_x = 0.666;//rotation center x
double Params::rot_y = 0.5;//rotation center y

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
	__attr__["patch_width_min"] = make_pair("int", static_cast<void*>(&patch_width_min));
	__attr__["patch_pixel_min"] = make_pair("float", static_cast<void*>(&patch_pixel_min));
	__attr__["patch_pixel_max"] = make_pair("float", static_cast<void*>(&patch_pixel_max));
	__attr__["morph_min"] = make_pair("float", static_cast<void*>(&morph_min));
	__attr__["morph_canny_low_thr"] = make_pair("double", static_cast<void*>(&morph_canny_low_thr));
	__attr__["morph_canny_up_thr"] = make_pair("double", static_cast<void*>(&morph_canny_up_thr));
	__attr__["morph_size"] = make_pair("int", static_cast<void*>(&morph_size));
	__attr__["morph_scale"] = make_pair("int", static_cast<void*>(&morph_scale));
	__attr__["morph_smooth_ksize"] = make_pair("int", static_cast<void*>(&morph_smooth_ksize));
	__attr__["morph_fill_all"] = make_pair("bool", static_cast<void*>(&morph_fill_all));

	__attr__["egbis_sigma"] = make_pair("float", static_cast<void*>(&egbis_sigma));
	__attr__["egbis_c"] = make_pair("float", static_cast<void*>(&egbis_c));
	__attr__["egbis_min_size"] = make_pair("int", static_cast<void*>(&egbis_min_size));

	__attr__["shape_context_sample_point_num"] = make_pair("int", static_cast<void*>(&shape_context_sample_point_num));
	__attr__["shape_context_bending_weight"] = make_pair("float", static_cast<void*>(&shape_context_bending_weight));
	__attr__["shape_context_match_weight"] = make_pair("float", static_cast<void*>(&shape_context_match_weight));
	__attr__["shape_context_appearance_weight"] = make_pair("float", static_cast<void*>(&shape_context_appearance_weight));
	__attr__["shape_context_use_rotation"] = make_pair("bool", static_cast<void*>(&shape_context_use_rotation));
	__attr__["shape_context_iterations"] = make_pair("int", static_cast<void*>(&shape_context_iterations));
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
	__attr__["xmlFileName"] = make_pair("string", static_cast<void*>(&xmlFileName));
	__attr__["pageSize"] = make_pair("int", static_cast<void*>(&pageSize));
	__attr__["pixel_valid_thr"] = make_pair("double", static_cast<void*>(&pixel_valid_thr));

	__attr__["generation_height"] = make_pair("int", static_cast<void*>(&generation_height));
	__attr__["generation_width"] = make_pair("int", static_cast<void*>(&generation_width));
	__attr__["patch_scale"] = make_pair("int", static_cast<void*>(&patch_scale));
	__attr__["angle"] = make_pair("double", static_cast<void*>(&angle));
	__attr__["rot_x"] = make_pair("double", static_cast<void*>(&rot_x));
	__attr__["rot_y"] = make_pair("double", static_cast<void*>(&rot_y));
}

void Params::set_attr(const char *name,const char * value){
    string p_type;
    map<string, pair<string, void*> >::iterator it;
    if (name && value){
        it = Params::__attr__.find(name);
        if (it != Params::__attr__.end()) {
            p_type = (it->second).first;
            if (p_type == "float") {
                *((float *)((it->second).second)) = atof(value);
            }else if(p_type == "double"){
                *((double *)((it->second).second)) = atof(value);
            }else if(p_type == "int"){
                *((int *)((it->second).second)) = atoi(value);
            }else if(p_type == "bool"){
                *((bool *)((it->second).second)) = (bool) atoi(value);
            }else if(p_type == "string"){
                *((string *)((it->second).second)) = string(value);
            }else{
                //Error
            }
        }else{
            //No such parameter: para_name
        }
    }
}

