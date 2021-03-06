#include "segment_algorithm.h"
#include <vector>
#include "params.h"
#include <cv.h>
#include "egbis_segment_image.h"

Mat & SimplePre(Mat & org, Mat & result)
{
	if (org.channels() > Params::grey_image_channels)
		cvtColor(org, result, CV_BGR2GRAY, Params::grey_image_channels);
	else
		result = org.clone();
	result.convertTo(result, Params::grey_image_type);
	medianBlur(result, result, Params::morph_smooth_ksize);
	resize(result, result, Size(Params::morph_scale * org.rows, Params::morph_scale * org.cols));
	return result;
}

void param_adaptor(string segment_type, bool too_many)
{
	if (too_many)
	{
		if (segment_type == Params::MORPH_BASIC)
		{
			Params::morph_min *= (1 + Params::segment_step);
		}
		else if (segment_type == Params::EGBIS)
		{
			Params::egbis_c += Params::egbis_c * Params::segment_step;
		}
	}
	else
	{
		if (segment_type == Params::MORPH_BASIC)
		{
			Params::morph_min *= (1 - Params::segment_step);
		}
		else if (segment_type == Params::EGBIS)
		{
			Params::egbis_c -= Params::egbis_c * Params::segment_step;
		}
	}
}

int CannyAndMorphing(Mat & input, Mat & result)
{
	Mat temp = Mat(input.size(), CV_8UC1);
	Canny(input, temp, Params::morph_canny_low_thr, Params::morph_canny_up_thr);
	dilate(temp, temp, noArray());
	Mat element5(Params::morph_size, Params::morph_size, CV_8U, Scalar(1));
	morphologyEx(temp, temp, MORPH_CLOSE, element5);
	resize(temp, temp, Size(input.rows / Params::morph_scale, input.cols / Params::morph_scale), .0f, .0f, INTER_LINEAR);
	temp = temp >= Params::morph_min;
	//temp.convertTo(temp, CV_8UC1);
	//
	// return FindRegFromEdge(result);
	vector<vector<Point>> edges;
	vector<Vec4i> hierarchy;
	findContours(temp, edges, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	int index = 1;
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
		//drawContours(result, edges, idx, Scalar(index++));
		drawContours(result, edges, idx, Scalar(index++), Params::morph_fill_all?CV_FILLED:1);
	return index -= 1;
}

int egbis(Mat & input, Mat & result)
{
	int connect_sum = 0;
	Mat color_ret;
	result = egbis_segment_image(input, color_ret, &connect_sum,Params::egbis_sigma,Params::egbis_c,Params::egbis_min_size);
	return connect_sum;
}