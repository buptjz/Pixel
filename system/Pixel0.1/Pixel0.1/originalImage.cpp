#include<opencv2/imgproc/imgproc.hpp>
#include"originalImage.h"
/*
将图片信息存入数据库中
会首先调用数据库的连接，向数据库中写入
图像名（originalImageId）、图像路径(path)
*/

/**/
static const Mat & prePareImage(Mat &, Mat &);
/* 输入连通图， 区域数，返回小图元的位置信息
CvRect 创造语句:
CvRect *rects = new CvRect[count]*/
static vector<Rect *> & getMetaInfos(const Mat &, vector<Rect *> &, int);
static vector<Rect *> & getMetaInfos(vector<vector<Point>> &, vector<Rect *> &);
static void AdaptiveFindThreshold(Mat & ima, double & low, double & high, int aperture_size = 3);

OriginalImage::OriginalImage(){}

void OriginalImage::saveOriginalImage(SQLiteHelper &sql_lite_helper) const{};

vector<Rect *> & getMetaInfos(const Mat & img, vector<Rect *> & rects, int count)
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
	int height = img.rows;
	int width = img.cols;
	int i, j, index;
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			index = *(img.data + img.step[0] * i + img.step[1] * j);
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
	delete[] regionIsMarked;
	return rects;
}

vector<Rect *> & getMetaInfos(vector<vector<Point>> & list, vector<Rect *> & rects)
{
	int count = list.size();
	int ** markRange = new int *[4];
	int * temp = new int[4 * count];
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
分割一幅大图像为众多小图元，大图像为类OriginalImage的私有变量
小图元以对象指针的list形式返回
*/
vector<ImagePatch*> OriginalImage::segmentImage() const
{
	Mat preImg(pOImage->rows, pOImage->cols, CV_8UC3);
	Mat grayImg, medianImg, edgeImg, morphImg;
	preImg = prePareImage(*pOImage, preImg);
	int count = 0;
	vector<ImagePatch*> result;
	//	
	cvtColor(preImg, grayImg, CV_RGB2GRAY);
	medianBlur(grayImg, medianImg, 3);
	resize(medianImg, medianImg, Size(3 * pOImage->rows, 3 * pOImage->cols));
	//
	//double low, high;
	//AdaptiveFindThreshold(medianImg, low, high);
	Canny(medianImg, edgeImg, 50, 150);
	dilate(edgeImg, morphImg, noArray());
	Mat element5(5, 5, CV_8U, Scalar(1));
	morphologyEx(morphImg, morphImg, MORPH_CLOSE, element5);
	//namedWindow("s");
	//imshow("s", morphImg);
	//waitKey(10);
	//
	vector<vector<Point>> contours;
	findContours(morphImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect *> rects;
	rects = getMetaInfos(contours, rects);
	//
	ImagePatch * imgPatch;
	for (int index = 1; index <= count; ++index)
	{
		Rect * rect = rects.at(index - 1);
		string id = originalImageId + "_imagePatch_" + index;
		Mat bip(*pOImage, *rect);
		Mat oip = bip == index;
		imgPatch = new ImagePatch(id, const_cast<OriginalImage *>(this), *rect, &bip, &oip);
	}
	for (vector<Rect *>::iterator it = rects.begin(); it != rects.end(); ++it)
		delete *it;
	return result;
}

const Mat & prePareImage(Mat & img, Mat & rimg)
{
	rimg = img.clone();
	return rimg;
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