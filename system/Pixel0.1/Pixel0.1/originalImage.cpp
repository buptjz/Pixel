#include"originalImage.h"
#include "sqlliteHelper.h"
/*
��ͼƬ��Ϣ�������ݿ���
�����ȵ������ݿ�����ӣ������ݿ���д��
ͼ������originalImageId����ͼ��·��(path)
*/
static Mat & SimplePre(Mat &, Mat &);
static void AdaptiveFindThreshold(Mat & ima, double & low, double & high, int aperture_size = 3);
static int CannyAndMorphing(Mat &, Mat &);
/* Mat�����ǵ�ͨ����*/
static int FindRegFromEdge(Mat &);

//void OriginalImage::saveOriginalImage(SQLiteHelper &sql_lite_helper) const{};
void OriginalImage::saveOriginalImage()const
{
	std::stringstream str_sql;
	str_sql << "insert into originalImage values(";
	str_sql << originalImageId << "," << path << ");";
	std::string str = str_sql.str();
	SQLiteHelper::Insert(str.c_str());
}

vector<Rect *> & OriginalImage::getMetaInfos(vector<Rect *> & rects, int count) const
{
	/* ��ʶһ�������Ƿ���ʹ�*/
	bool * regionIsMarked = new bool[count];
	memset(regionIsMarked, 0, count);
	/* �洢һ���������С�߶�λ�á����߶�λ�á���С���λ�á������λ��*/
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
	Rect *rect = new Rect();
	// ��λ����ϢתΪΪRect
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

const int OriginalImage::segAlgorithm(Mat & input, int (*algo)(Mat &, Mat &)) const
{
	return algo(input, *regImage);
}

vector<Rect *> & OriginalImage::getMetaInfos(vector<vector<Point>> & list, vector<Rect *> & rects) const
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
	// ��λ����ϢתΪΪRect
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
�ָ�һ����ͼ��Ϊ�ڶ�СͼԪ����ͼ��Ϊ��OriginalImage��˽�б���
СͼԪ�Զ���ָ���list��ʽ����
*/
vector<ImagePatch*> OriginalImage::segmentImage()
{	
	Mat preImg;
	preImg = prePareImage(preImg, SimplePre);
	//double low, high;
	//AdaptiveFindThreshold(medianImg, low, high);
	Mat t = Mat::zeros(pOImage->size(), CV_16UC1);
	regImage = &t;
	//namedWindow("s");
	//imshow("s", morphImg);
	//waitKey(10);
	int coupreImgnt = segAlgorithm(preImg, CannyAndMorphing);
	//
	//vector<vector<Point>> contours;
	//findContours(preImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect *> rects;
	rects = getMetaInfos(rects, coupreImgnt);
	//
	vector<ImagePatch*> result;
	ImagePatch * imgPatch;
	for (int index = 1; index <= coupreImgnt; ++index)
	{
		Rect * rect = rects.at(index - 1);
		string id = originalImageId + "_imagePatch_" + index;
		Mat bip(*pOImage, *rect);
		Mat oip = bip == index;
		imgPatch = new ImagePatch(id, const_cast<OriginalImage *>(this), *rect, &bip, &oip);
		result.push_back(imgPatch);
	}
	for (vector<Rect *>::iterator it = rects.begin(); it != rects.end(); ++it)
		delete *it;
	return result;
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
	// ����ߵ�����                                                          
	high = (i + 1) * histSizeMax;
	low = high * 0.4;
}

Mat & SimplePre(Mat & org, Mat & result)
{
	cvtColor(org, result, CV_RGB2GRAY);
	medianBlur(result, result, 3);
	resize(result, result, Size(3 * org.rows, 3 * org.cols));
	return result;
}

int CannyAndMorphing(Mat & input, Mat & result)
{
	Mat temp = Mat(input.size(), CV_8UC1);
	Canny(input, temp, 50, 150);
	dilate(temp, temp, noArray());
	Mat element5(5, 5, CV_8U, Scalar(1));
	morphologyEx(temp, temp, MORPH_CLOSE, element5);
	resize(temp, temp, Size(input.rows / 3, input.cols / 3), .0f, .0f, INTER_LINEAR);
	temp=temp >= .4;
	//temp.convertTo(temp, CV_8UC1);
	//
	// return FindRegFromEdge(result);
	vector<vector<Point>> edges;
	vector<Vec4i> hierarchy;
	findContours(temp, edges, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	int index = 1;
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
		drawContours(result, edges, idx, Scalar(index++), CV_FILLED);
	return index-=1;
}

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
