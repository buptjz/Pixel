#include "patch.h"
#include "params.h"
#include "opencv2/shape.hpp"
#include "opencv2/imgproc.hpp"
#include <queue>
#include<functional>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include "sqlliteHelper.h"
#include "surfMatch.h"
#include "jsonHelper.h"
#include <map>
/*和当前图元进行比较
*输入：待比较的图元，比较时使用的特征种类
*输出：本图元和待比较的图元的相似度
*/
cv::Ptr <cv::ShapeContextDistanceExtractor> sc_extractor = cv::createShapeContextDistanceExtractor();

static void refresh_sc_extractor_settings()
{
	sc_extractor->setShapeContextWeight(Params::shape_context_match_weight);
	sc_extractor->setBendingEnergyWeight(Params::shape_context_bending_weight);
	sc_extractor->setImageAppearanceWeight(Params::shape_context_appearance_weight);
	sc_extractor->setRotationInvariant(Params::shape_context_use_rotation);
}

//currentQuery must be gray image with 1 channel. if not , it will be converted into 1 channel
static vector<Point> simpleContour( Mat& currentQuery, int n = 80 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;
	if(currentQuery.channels() > 1)
		cvtColor(currentQuery,currentQuery,CV_BGR2GRAY,1);
	cv::findContours(currentQuery.clone(), _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }
	vector<Point> cont;
	if(contoursQuery.size() == 0)
		return cont;
    // In case actual number of points is less than n
    int dummy=0;
    for (int add=(int)contoursQuery.size()-1; add<n; add++)
    {
        contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
    }

    // Uniformly sampling
    random_shuffle(contoursQuery.begin(), contoursQuery.end());
    
    for (int i=0; i<n; i++)
    {
        cont.push_back(contoursQuery[i]);
    }
    return cont;
}
static void _compare_sift(Patch *query, const vector<Patch *>& images, vector<double> &ret, bool useBinary = true)
{
}
static void _compare_sc(Patch *query, const vector<Patch *>& images, vector<double> &ret)
{
	refresh_sc_extractor_settings();
	ret.clear();
	ret.resize(images.size(), DBL_MAX);
	vector<Point> contQuery = simpleContour(*query->getBinaryImagePatch(),Params::shape_context_sample_point_num);
	if (contQuery.size() < Params::shape_context_sample_point_num)
		return;
	size_t cnt = 0;
	for(vector<Patch *>::const_iterator itr = images.begin(); itr != images.end(); ++itr,++cnt)
	{
		Patch* ptr = *itr;
		vector<Point> contii = simpleContour(*ptr->getBinaryImagePatch(),Params::shape_context_sample_point_num);
		if (contii.size() < Params::shape_context_sample_point_num)
			return;
		if(abs(Params::shape_context_appearance_weight) > 0.0001)
			sc_extractor->setImages(*query->getOriginalImagePatch(),*ptr->getOriginalImagePatch());
		ret[cnt] = (sc_extractor->computeDistance(contQuery,contii));
	}
	
}

static void _compare_surf(Patch *query, const vector<Patch *>& images, vector<double> &ret)
{
	ret.clear();
	map<string, string > query_featuremap = query->getFeatures();
	Mat query_feature,image_feature;
	if (query_featuremap.size() == 0 || query_featuremap.count(Params::SURF) == 0)
	{
		string feature_str;
		generate_surf_descriptors(*query->getOriginalImagePatch(),query_feature);
		if (query_feature.rows < Params::surf_descriptor_min)
			query_feature = Mat();
		mat2jsonString(query_feature, feature_str);
		query->addFeature(make_pair(Params::SURF, feature_str));
	}
	else
	{
		jsonString2Mat(query_featuremap[Params::SURF], query_feature);
	}
	for (size_t i = 0; i < images.size(); ++i)
	{
		Patch* patch_ptr = images[i];
		Mat image_feature;
		map<string, string> image_featuremap = patch_ptr->getFeatures();
		if (image_featuremap.size() == 0 || image_featuremap.count(Params::SURF) == 0)
		{
			string feature_str;
			generate_surf_descriptors(*patch_ptr->getOriginalImagePatch(), image_feature);
			if (image_feature.rows < Params::surf_descriptor_min)
				image_feature = Mat();
			mat2jsonString(image_feature, feature_str);
			patch_ptr->addFeature(make_pair(Params::SURF, feature_str));
		}
		else
			jsonString2Mat(image_featuremap[Params::SURF], image_feature);
		if (image_feature.data == NULL || query_feature.data == NULL)
			ret.push_back(0);
		else
			ret.push_back(surf_match_score_with_descriptor(query_feature, image_feature));
	}
}

vector<double> Patch::patchCompareWith(const vector<Patch*> &images, const string featureType)
{
	vector<double> ret;
	if(featureType == Params::SHAPE_CONTEXT)
		_compare_sc(this,images,ret);
	else if (featureType == Params::SIFT)
		_compare_sift(this, images, ret);
	else if (featureType == Params::SURF)
		_compare_surf(this, images, ret);
	return ret;
}

double Patch::patchCompareWith(Patch *pPatch, const string featureType) 
{
	vector<Patch*> vec;
	vec.push_back(pPatch);
	vector<double> ret(patchCompareWith(vec,featureType));
	if(ret.empty())
		return -1;
	else
		return ret[0];
}

struct sc_cmp_func 
{
	bool operator()(pair<double, Patch*> left, pair<double, Patch*> right)
	{
		return left.first > right.first;
	}
};

struct surf_cmp_func
{
	bool operator()(pair<double, Patch*> left, pair<double, Patch*> right)
	{
		return right.first > left.first;
	}
};

vector<pair<double,Patch*> > Patch::patchCompareWith(const vector<Patch*>& images, const string featureType, size_t top_k)
{
	vector<double> score(patchCompareWith(images,featureType));
	vector<pair<double, Patch*> > ret;

	if (featureType == Params::SHAPE_CONTEXT)
	{
		priority_queue<pair<double, Patch *>, vector<pair<double, Patch*> >, sc_cmp_func > heap;
		for (size_t i = 0; i < score.size(); ++i)
		{
			heap.push(make_pair(score[i], images[i]));
		}
		for (size_t i = 0; i < top_k; ++i)
		{
			ret.push_back(heap.top());
			heap.pop();
		}
	}
	else if (featureType == Params::SURF)
	{
		priority_queue<pair<double, Patch *>, vector<pair<double, Patch*> >, surf_cmp_func > heap;
		for (size_t i = 0; i < score.size(); ++i)
		{
			heap.push(make_pair(score[i], images[i]));
		}
		for (size_t i = 0; i < top_k; ++i)
		{
			ret.push_back(heap.top());
			heap.pop();
		}
	}
	
	return ret;
}
