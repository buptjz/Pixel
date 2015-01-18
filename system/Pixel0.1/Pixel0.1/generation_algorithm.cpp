#include <opencv2/opencv.hpp>
#include "params.h"
#include "tools.h"
#include <time.h>
using namespace cv;

static const int copy_times = 2;

bool flip_mat(const Mat& src, Mat& dst, bool up_down = true)
{
	if (src.size != dst.size || src.data == NULL || src.channels() != 3 || src.type() != dst.type())
		return false;
	size_t elemSize = src.elemSize();
	if (up_down)
	{
		for (size_t i = 0; i < src.rows; ++i)
		{
			const uchar* src_row_ptr = src.ptr<uchar>(i);
			uchar* dst_row_ptr = dst.ptr<uchar>(src.rows - i - 1);
			for (size_t j = 0; j < src.cols; ++j)
			{
				*(dst_row_ptr + j * elemSize) = *(src_row_ptr + j * elemSize);
				*(dst_row_ptr + j * elemSize + 1) = *(src_row_ptr + j * elemSize + 1);
				*(dst_row_ptr + j * elemSize + 2) = *(src_row_ptr + j * elemSize + 2);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < src.rows; ++i)
		{
			const uchar* src_row_ptr = src.ptr<uchar>(i);
			uchar* dst_row_ptr = dst.ptr<uchar>(i);
			for (size_t j = 0; j < src.cols; ++j)
			{
				*(dst_row_ptr + ( src.cols - 1 - j ) * elemSize) = *(src_row_ptr + j * elemSize);
				*(dst_row_ptr + (src.cols - 1 - j) * elemSize + 1) = *(src_row_ptr + j * elemSize + 1);
				*(dst_row_ptr + (src.cols - 1 - j) * elemSize + 2) = *(src_row_ptr + j * elemSize + 2);
			}
		}
	}
}

Mat* generat_rot(const Mat* src_const)
{
	if (src_const == NULL || src_const->channels() != Params::color_image_channels)
		return NULL;

	Mat src;
	resize(*src_const, src, Size(floor(Params::patch_scale * sqrt(3)), Params::patch_scale));

	size_t elem_size = src.elemSize();


	Mat non_rot(Mat::zeros(src.rows * copy_times, src.cols, src.type()));

	Mat flip(src.rows, src.cols, src.type());
	if (!flip_mat(src, flip, true))
		return NULL;
	
	for (size_t i = 0; i < non_rot.rows; ++i)
	{
		uchar* dst_ptr = non_rot.ptr<uchar>(i);
		const uchar* src_ptr = i < flip.rows ? flip.ptr<uchar>(i) : src.ptr<uchar>(i - flip.rows);
		for (size_t j = 0; j < non_rot.cols; ++j)
		{
			*(dst_ptr + j * elem_size) = *(src_ptr + j * elem_size);
			*(dst_ptr + j * elem_size + 1) = *(src_ptr + j * elem_size + 1);
			*(dst_ptr + j * elem_size + 2) = *(src_ptr + j * elem_size + 2);
		}
	}
	
	//tool_show_mat(non_rot, "mirror");
	Mat rot1_trans_mat = getRotationMatrix2D(Point2f(Params::rot_x*non_rot.cols, Params::rot_y*non_rot.rows), Params::angle, 1);
	Mat rot2_trans_mat = getRotationMatrix2D(Point2f(Params::rot_x*non_rot.cols, Params::rot_y*non_rot.rows), -Params::angle, 1);
	Mat rot1,rot2;
	warpAffine(non_rot, rot1, rot1_trans_mat, non_rot.size());
	warpAffine(non_rot, rot2, rot2_trans_mat, non_rot.size());
	//tool_show_mat(rot1, "mirror_rot1");
	//tool_show_mat(rot2, "mirror_rot2");
	RNG rng(time(0));
	Mat *ret = new Mat(non_rot.rows * (Params::generation_height + 1), non_rot.cols * (Params::generation_width + 1), non_rot.type());
	Mat *tmp1 = NULL, *tmp2 = NULL;
	for (size_t ni = 0; ni < Params::generation_height; ++ni)
	{
		for (size_t nj = 0; nj < Params::generation_width; ++nj)
		{
			int rng_num = rng.uniform(0, 3);
			if (rng_num == 0)
				tmp1 = &non_rot;
			else if (rng_num == 1)
				tmp1 = &rot1;
			else if (rng_num == 2)
				tmp1 = &rot2;
			else
				cout << rng_num;

			rng_num = rng.uniform(0, 3);
			if (rng_num == 0)
				tmp2 = &non_rot;
			else if (rng_num == 1)
				tmp2 = &rot1;
			else if (rng_num == 2)
				tmp2 = &rot2;
			else
				cout << rng_num;

			if (nj % 2 == 0)
			{
				for (size_t i = 0; i < non_rot.rows; ++i)
				{
					for (size_t j = 0; j < non_rot.cols; ++j)
					{
						if (i > double(j) / sqrt(3) && non_rot.rows - 1 - i > double(j) / sqrt(3))
						{
							ret->at<Vec3b>(ni*(non_rot.rows) + i , nj * non_rot.cols + j)[0] = tmp1->at<Vec3b>(i, j)[0];
							ret->at<Vec3b>(ni*(non_rot.rows) + i , nj * non_rot.cols + j)[1] = tmp1->at<Vec3b>(i, j)[1];
							ret->at<Vec3b>(ni*(non_rot.rows) + i , nj * non_rot.cols + j)[2] = tmp1->at<Vec3b>(i, j)[2];

							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[0] = tmp2->at<Vec3b>(i, j)[0];
							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[1] = tmp2->at<Vec3b>(i, j)[1];
							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[2] = tmp2->at<Vec3b>(i, j)[2];
						}
					}
				}
			}
			else
			{
				for (size_t i = 0; i < non_rot.rows; ++i)
				{
					for (size_t j = 0; j < non_rot.cols; ++j)
					{
						if (i > double(j) / sqrt(3) && non_rot.rows - 1 - i > double(j) / sqrt(3))
						{
							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , nj * non_rot.cols + j)[0] = tmp1->at<Vec3b>(i, j)[0];
							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , nj * non_rot.cols + j)[1] = tmp1->at<Vec3b>(i, j)[1];
							ret->at<Vec3b>(ni*(non_rot.rows) + floor(0.5 * non_rot.rows) + i , nj * non_rot.cols + j)[2] = tmp1->at<Vec3b>(i, j)[2];

							ret->at<Vec3b>(ni*(non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[0] = tmp2->at<Vec3b>(i, j)[0];
							ret->at<Vec3b>(ni*(non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[1] = tmp2->at<Vec3b>(i, j)[1];
							ret->at<Vec3b>(ni*(non_rot.rows) + i , (nj + 1) * non_rot.cols - 1 - j)[2] = tmp2->at<Vec3b>(i, j)[2];
						}
					}
				}
			}

		}
	}
	//tool_show_mat(*ret, "ret");
	return ret;
}