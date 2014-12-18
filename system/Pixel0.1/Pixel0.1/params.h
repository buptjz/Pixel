#ifndef _PARAMS_H_
#define _PARAMS_H_

class Params
{
public:
	//some flages
	static const string SIFT;
	static const string SHAPE_CONTEXT;

	//params for match
	static int shape_context_sample_point_num;
	static float shape_context_bending_weight;
	static float shape_context_match_weight;
	static float shape_context_appearance_weight;
	static bool shape_context_use_rotation;
};

//some flages
const string Params::SIFT = "SIFT";
const string Params::SHAPE_CONTEXT = "SHAPE_CONTEXT";

//params for match
int Params::shape_context_sample_point_num = 100;
float Params::shape_context_bending_weight = 0;
float Params::shape_context_match_weight = 1;
float Params::shape_context_appearance_weight = 0;
bool Params::shape_context_use_rotation = false;

#endif