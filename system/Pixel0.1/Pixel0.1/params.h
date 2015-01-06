#ifndef _PARAMS_H_
#define _PARAMS_H_

//#include <iostream>

#include <string>
#include <map>
using namespace std;

#define __DEBUG__

class Params
{
public:
	//a map which contains all the non-constant attributs
	static map<string, pair<string, void*> > __attr__;
	static void push_attr();
	
	//some flages
	static const string SIFT;
	static const string SHAPE_CONTEXT;
	static const string SURF;
	static const string MORPH_BASIC;
	static const string EGBIS;
	
	//params for images
	static int color_image_type;
	static int color_image_channels;
	static int grey_image_type;
	static int grey_image_channels;
	static int connect_map_type;

	//params for segment
	static double pixel_rat_min;
	static int retry_max;//if segment failed, the max times algorithm can retry.
	static float segment_expect_upboard;
	static float segment_expect_lowboard;
	static int segment_expect;
	static float segment_step;

	static float patch_pixel_min;
	static float patch_pixel_max;
	static float morph_min;
	static float egbis_sigma;
	static float egbis_c;
	static int egbis_min_size;

	//params for match
	static int shape_context_sample_point_num;
	static float shape_context_bending_weight;
	static float shape_context_match_weight;
	static float shape_context_appearance_weight;
	static bool shape_context_use_rotation;
	static int surf_descriptor_min; //min number of surf descriptors
    
    //shape context compare
    //similar score <= this threshold will be regarded as the same images
    static double shape_context_compare_1_thres;
    static double shape_context_compare_2_thres;
	static double surf_compare_1_thres;
	static double surf_compare_2_thres;
    
    //surf
    static int surf_dimensions;
    static double surf_min_ratio;


	static string featureType_for_one_image;//featureType used 
	static string featureType_for_batch_image;
	static string featureType_for_search;
	static string segment_type_for_one_image;
	static string segment_type_for_batch_image;
	static int top_k;//return the top_k simplar superImagePatches

	static string defaultPath;
};


#endif