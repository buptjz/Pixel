#include "patch.h"
#include "opencv2/shape.hpp"
#include "opencv2/imgproc.hpp"
/*�͵�ǰͼԪ���бȽ�
*���룺���Ƚϵ�ͼԪ���Ƚ�ʱʹ�õ���������
*�������ͼԪ�ʹ��Ƚϵ�ͼԪ�����ƶ�
*/
cv::Ptr <cv::ShapeContextDistanceExtractor> sc_extractor = cv::createShapeContextDistanceExtractor();
static vector<Point> simpleContour( const Mat& currentQuery, int n=80 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;
    cv::findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
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
static void _compare_sc(Patch *query, const vector<Patch *>& images, vector<double> &ret, bool useBinary = true)
{
	ret.clear();
	vector<Point> contQuery;
	if(useBinary)
		contQuery = simpleContour(*query->getBinaryImagePatch());
	else
		contQuery = simpleContour(*query->getOriginalImagePatch());
	for(vector<Patch *>::const_iterator itr = images.begin(); itr != images.end(); ++itr)
	{
		Patch* ptr = *itr;
		vector<Point> contii;
		if(useBinary)
			contii = simpleContour(*ptr->getBinaryImagePatch());
		else
			contii = simpleContour(*ptr->getOriginalImagePatch());
		ret.push_back(sc_extractor->computeDistance(contQuery,contii));

	}

}

vector<double> Patch::patchCompareWith(const vector<Patch*> &images, string featureType)
{
	vector<double> ret;
	if(featureType == "SHAPE_CONTEXT")
		_compare_sc(this,images,ret);
	else if(featureType == "SIFT")
		_compare_sift(this,images,ret);

	return ret;
}

double Patch::patchCompareWith(Patch *pPatch, string featureType) 
{
	vector<Patch*> vec;
	vec.push_back(pPatch);
	vector<double> ret(patchCompareWith(vec,featureType));
	if(ret.empty())
		return -1;
	else
		return ret[0];
}