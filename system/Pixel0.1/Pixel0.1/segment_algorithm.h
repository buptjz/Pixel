#ifndef __SEGMENT_ALGORITHM_H__
#define __SEGMENT_ALGORITHM_H__

#include <opencv.hpp>
using namespace cv;
using namespace std;

Mat & SimplePre(Mat &, Mat &);
int CannyAndMorphing(Mat &, Mat &);
int egbis(Mat &, Mat &);
void param_adaptor(string segment_type, bool too_many);

#endif