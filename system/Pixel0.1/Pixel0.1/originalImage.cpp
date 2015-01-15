#include"originalImage.h"
#include "sqlliteHelper.h"
#include "params.h"
#include "tools.h"
#include "segment_algorithm.h"
#include "logDisplay.h"
/*
将图片信息存入数据库中
会首先调用数据库的连接，向数据库中写入
图像名（originalImageId）、图像路径(path)
*/
static void AdaptiveFindThreshold(Mat & ima, double & low, double & high, int aperture_size = 3);
/* Mat必须是单通道的*/
static int FindRegFromEdge(Mat &);
extern LogDisplay *logDisplay;
//void OriginalImage::saveOriginalImage(SQLiteHelper &sql_lite_helper) const{};
void OriginalImage::saveOriginalImage()const
{
	std::stringstream str_sql;
	str_sql << "insert into originalImage values('";
	str_sql << originalImageId << "','" << path << "');";
	std::string str = str_sql.str();
	SQLiteHelper::Insert(str.c_str());
}

vector<Rect *> & OriginalImage::getMetaInfos(vector<Rect *> & rects, int count) const
{
	/* 标识一个区域是否访问过*/
	bool * regionIsMarked = new bool[count];
	memset(regionIsMarked, 0, count);
	/* 存储一个区域的最小高度位置、最大高度位置、最小宽度位置、最大宽度位置*/
	int ** markRange = new int *[4];
	int * temp = new int[4 * count];
	for (int t = 0; t < 4; ++t)
		markRange[t] = temp + t*count;
	//
	Mat img = *regImage;
	int height = img.rows;
	int width = img.cols;
	int i, j, index;
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			index = *(img.data + img.step[0] * i + img.step[1] * j);
			assert(index <= count);
			if (index == 0)
				continue;
			else if (regionIsMarked[index - 1])
			{
				if (markRange[0][index - 1] > i)					markRange[0][index - 1] = i;
				else if (markRange[1][index - 1] < i)			markRange[1][index - 1] = i;
				if (markRange[2][index - 1] > j)					markRange[2][index - 1] = j;
				else if (markRange[3][index - 1] < j)			markRange[3][index - 1] = j;
			}
			else
			{
				regionIsMarked[index - 1] = true;
				markRange[0][index - 1] = i;
				markRange[1][index - 1] = i;
				markRange[2][index - 1] = j;
				markRange[3][index - 1] = j;
			}
		}
	}
	Rect *rect;
	// 将位置信息转为为Rect
	for (i = 0; i < count; ++i)
	{
		//rect = new Rect(markRange[0][i], markRange[2][i], markRange[1][i] - markRange[0][i] + 1, markRange[3][i] - markRange[2][i] + 1);
		rect = new Rect(markRange[2][i], markRange[0][i], markRange[3][i] - markRange[2][i] + 1, markRange[1][i] - markRange[0][i] + 1);
		rects.push_back(rect);
	}
	//
	delete[] temp;
	delete[] markRange;
	delete[] regionIsMarked;
	return rects;
}

const int OriginalImage::segAlgorithm(Mat & input, int (*algo)(Mat &, Mat &)) const
{
	return algo(input, *regImage);
}

vector<Rect *> & OriginalImage::getMetaInfos(vector<vector<Point>> & list, vector<Rect *> & rects) const
{
	int count = list.size();
	int ** markRange = new int *[4];
	int * temp = new int[4 * count];
	memset(temp, 0, 4 * count * sizeof(int));
	for (int t = 0; t < 4; ++t)
		markRange[t] = temp + t*count;
	//
	int i, j, index = 0;
	for (vector<vector<Point>>::iterator v1 = list.begin(); v1 != list.end(); ++v1)
	{
		++index;
		vector<Point> vt = *v1;
		vector<Point>::iterator v2 = (*v1).begin();
		i = (*v2).x;
		j = (*v2).y;
		markRange[0][index - 1] = i;
		markRange[1][index - 1] = i;
		markRange[2][index - 1] = j;
		markRange[3][index - 1] = j;
		for (v2 += 1; v2 != (*v1).end(); ++v2)
		{
			i = (*v2).x;
			j = (*v2).y;
			if (markRange[0][index - 1] > i)					markRange[0][index - 1] = i;
			else if (markRange[1][index - 1] < i)			markRange[1][index - 1] = i;
			if (markRange[2][index - 1] > j)					markRange[2][index - 1] = j;
			else if (markRange[3][index - 1] < j)			markRange[3][index - 1] = j;
		}
	}
	Rect *rect = new Rect();
	// 将位置信息转为为Rect
	for (i = 0; i < count; ++i)
	{
		rect = new Rect(markRange[0][i], markRange[2][i], markRange[1][i] - markRange[0][i] + 1, markRange[3][i] - markRange[2][i] + 1);
		rects.push_back(rect);
	}
	//
	delete[] temp;
	delete[] markRange;
	return rects;
}
/*
compute the ratio of non-zero pixel of a Mat.
*/
double get_pixel_rat(const Mat& input)
{
	if (input.data == NULL || input.cols == 0 || input.rows == 0)
		return 0;
	Mat tmp;
	if (input.channels() > 1)
		cvtColor(input, tmp, CV_BGR2GRAY, 1);
	else
		tmp = input;
	tmp.convertTo(tmp, Params::grey_image_type);
	int sum = tmp.rows * tmp.cols;
	int cnt = 0;

	for (size_t i = 0; i < tmp.rows; ++i)
	{
		for (size_t j = 0; j < tmp.cols; ++j)
		{
			if (tmp.at<uchar>(i,j) > Params::pixel_valid_thr*255)
				++cnt;
		}
	}
	return double(cnt) / double(sum);
}

int OriginalImage::get_connected_map(string segment_type)
{
	Mat preImg;
	if (segment_type == Params::MORPH_BASIC)
		preImg = prePareImage(preImg, SimplePre);
	else if (segment_type == Params::EGBIS)
		preImg = pOImage->clone();
	else
		return 0;

	Mat *t = new Mat(Mat::zeros(pOImage->size(), Params::connect_map_type));
	if (regImage != NULL)
		delete regImage;
	regImage = t;
	int coupreImgnt = 0;
	for (int i = 0; i < Params::retry_max; ++i)
	{
		if (segment_type == Params::MORPH_BASIC)
			coupreImgnt = segAlgorithm(preImg, CannyAndMorphing);
		else if (segment_type == Params::EGBIS)
			coupreImgnt = segAlgorithm(preImg, egbis);
		else
			return 0;
		if (Params::segment_expect <= 0)
			break;
		else if (coupreImgnt < Params::segment_expect_lowboard * Params::segment_expect)
			param_adaptor(segment_type, false);
		else if (coupreImgnt > Params::segment_expect_upboard * Params::segment_expect)
			param_adaptor(segment_type, true);
		else
			break;
	}
	return coupreImgnt;
}

vector<ImagePatch*> OriginalImage::get_patches(int connect_num)
{
	vector<Rect *> rects;
	rects = getMetaInfos(rects, connect_num);

	vector<ImagePatch*> result;
	ImagePatch * imgPatch;
	string name = "image patch";//window name for show
	for (int index = 1; index <= connect_num; ++index)
	{
		Rect * rect = rects.at(index - 1);
		int org_size = pOImage->rows * pOImage->cols, rect_size = rect->width * rect->height;
		if (rect_size < org_size * Params::patch_pixel_min || rect_size > org_size * Params::patch_pixel_max)
			continue;
		stringstream ss;
		string str;
		ss << index;
		ss >> str;
		string id = originalImageId + "_imagePatch_" + str;
		Mat mask = ((*regImage)(*rect) == index);
		Mat org = Mat(*pOImage, *rect).clone();
		vector<Mat> masks;
		for (size_t i = 0; i < org.channels(); ++i)
			masks.push_back(mask);
		Mat mask_multichannel;
		merge(masks, mask_multichannel);
		Mat *oip = new Mat(org);
		bitwise_and(org, mask_multichannel, *oip);
		if (get_pixel_rat(*oip) < Params::pixel_rat_min)
			continue;
		cv::namedWindow(name);
		cv::imshow(name, *oip);
		waitKey(500);
		cv::destroyAllWindows();
		Mat *bip = new Mat(oip->rows, oip->cols, Params::grey_image_type);
		cvtColor(*oip, *bip, CV_BGR2GRAY, Params::grey_image_channels);

		imgPatch = new ImagePatch(id, const_cast<OriginalImage *>(this), *rect, bip, oip);
		result.push_back(imgPatch);
	}
	delete regImage;
	regImage = NULL;
	for (vector<Rect *>::iterator it = rects.begin(); it != rects.end(); ++it)
		delete *it;
	return result;
}

/*
分割一幅大图像为众多小图元，大图像为类OriginalImage的私有变量
小图元以对象指针的list形式返回
*/
vector<ImagePatch*> OriginalImage::segmentImage(string segment_type)
{	
	vector<ImagePatch*> ret;
	int connect_num = get_connected_map(segment_type);
	if (connect_num == 0)
		return ret;
#ifdef __DEBUG__
	Mat color_ret;
	connected_component2color_image(*regImage, connect_num, color_ret);
	//imshow("color_ret", color_ret);
	//waitKey(-1);
#endif
	return get_patches(connect_num);
	
}

const Mat & OriginalImage::prePareImage(Mat & preImg, Mat & (*pre)(Mat &, Mat &)) const
{
	return pre(*pOImage, preImg);
}

/* Adaptive Canny Threshold*/
void AdaptiveFindThreshold(Mat & ima, double & low, double & high, int aperture_size)
{
	Mat dx(ima.rows, ima.cols, CV_16SC1);
	Mat dy(ima.rows, ima.cols, CV_16SC1);
	Sobel(ima, dx, CV_32S, 1, 0, aperture_size);
	Sobel(ima, dy, CV_32S, 0, 1, aperture_size);
	Mat img = dx + dy;
	Mat hist;
	const int* channels = new int(0);
	double histSizeMax, histSizeMin;
	minMaxIdx(img, &histSizeMin, &histSizeMax);
	const int histSize = static_cast<int>(histSizeMax - histSizeMin + 1);
	float range[] = { static_cast<float>(histSizeMin), static_cast<float>(histSizeMax) };
	const float* histRange = { range };
	calcHist(&img, 1, channels, noArray(), hist, 1, &histSize, &histRange);
	float PercentOfPixelsNotEdges = 0.7f;
	int total = static_cast<int>(ima.rows* ima.cols* PercentOfPixelsNotEdges);
	int sum = 0, i = 0, s = hist.total();
	while (sum < s)
		// uchar 8bit data
		if ((sum += *(hist.data + hist.step*i++)) >= s)
			break;
	// 计算高低门限                                                          
	high = (i + 1) * histSizeMax;
	low = high * 0.4;
}

//bug ! marked by JZ
int FindRegFromEdge(Mat & img)
{
	int rows = img.rows, cols=img.cols, r, c;
	for (r = 0; r < rows; ++r)
	{
		short * data = reinterpret_cast<short*>(img.ptr<uchar>(r));
		for (c = 0; c < cols; ++c)
		{
			if (data[c]==1)
			{

			}
		}
	}
    return -1;
}

void OriginalImage::ShowRegion() const
{
	if (NULL == regImage)
		return;
	string name = originalImageId + "_Region";
	namedWindow(name);
	imshow(name, *regImage);
	waitKey();
};

void OriginalImage::ShowRects(const vector<ImagePatch *> & rects) const
{
	if (NULL == rects.size())
		return;
	//
	Mat temp = pOImage->clone();
	for (vector<ImagePatch *>::const_iterator it = rects.begin(); it != rects.end(); ++it)	
		rectangle(temp, (*it)->getPosition(), Scalar(RNG(255), RNG(255), RNG(255)));	
	string name = originalImageId + "_rects";
	namedWindow(name);
	imshow(name, temp);
	waitKey();
};
