#include "patch.h"
#include "params.h"
#include "opencv2/shape.hpp"
#include "opencv2/imgproc.hpp"
#include <queue>
#include<functional>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include "sqlliteHelper.h"
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

static vector<Point> simpleContour( const Mat& currentQuery, int n = 80 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;

	cv::findContours(currentQuery.clone(), _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }
    // In case actual number of points is less than n
    int dummy=0;
    for (int add=(int)contoursQuery.size()-1; add<n; add++)
    {
        contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
    }

    // Uniformly sampling
    random_shuffle(contoursQuery.begin(), contoursQuery.end());
    vector<Point> cont;
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
	vector<Point> contQuery = simpleContour(*query->getBinaryImagePatch(),Params::shape_context_sample_point_num);
	for(vector<Patch *>::const_iterator itr = images.begin(); itr != images.end(); ++itr)
	{
		Patch* ptr = *itr;
		vector<Point> contii = simpleContour(*ptr->getBinaryImagePatch(),Params::shape_context_sample_point_num);
		if(abs(Params::shape_context_appearance_weight) > 0.0001)
			sc_extractor->setImages(*query->getOriginalImagePatch(),*ptr->getOriginalImagePatch());
		ret.push_back(sc_extractor->computeDistance(contQuery,contii));
	}
	
}

vector<double> Patch::patchCompareWith(const vector<Patch*> &images, const string featureType)
{
	vector<double> ret;
	if(featureType == Params::SHAPE_CONTEXT)
		_compare_sc(this,images,ret);
	else if(featureType == Params::SIFT)
		_compare_sift(this,images,ret);

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

vector<pair<double,Patch*> > Patch::patchCompareWith(const vector<Patch*>& images, const string featureType, size_t top_k)
{
	vector<double> score(patchCompareWith(images,featureType));
	priority_queue<pair<double, Patch *>, vector<pair<double, Patch*> >, greater<pair<double,Patch*> > > heap;
	for(size_t i = 0;i < score.size();++i)
	{
		heap.push(make_pair(score[i],images[i]));
	}
	vector<pair<double,Patch*> > ret;
	for(size_t i = 0;i < top_k; ++i)
	{
		ret.push_back(heap.top());
		heap.pop();
	}
	return ret;
}
