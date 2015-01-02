#ifndef _PARAMS_H_
#define _PARAMS_H_

//#include <iostream>

#include <string>
using namespace std;

class Params
{
public:
	//some flages
	static const string SIFT;
	static const string SHAPE_CONTEXT;
	static const string SURF;
	
	//params for images
	static int color_image_type;
	static int color_image_channels;
	static int grey_image_type;
	static int grey_image_channels;
	static int connect_map_type;

	//params for segment
	static int patch_pixal_least;

	//params for match
	static int shape_context_sample_point_num;
	static float shape_context_bending_weight;
	static float shape_context_match_weight;
	static float shape_context_appearance_weight;
	static bool shape_context_use_rotation;
	static int surf_descriptor_min;
    
    //shape context compare
    //similar score <= this threshold will be regarded as the same images
    static double shape_context_compare_1_thres;
    static double shape_context_compare_2_thres;
	static double surf_compare_1_thres;
	static double surf_compare_2_thres;
    
    //surf
    static int surf_dimensions;
    static double surf_min_ratio;


	static string  featureType;//featureType used 
	static size_t top_k;//return the top_k simplar superImagePatches
};


#endif