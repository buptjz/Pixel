#include "originalImage.h"
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

void OriginalImage::saveOriginalImage() const
{

}

static vector<Rect *> & getMetaInfos(const Mat & img, vector<Rect *> & rects, int count)
{
	/* 标识一个区域是否访问过*/
	bool * regionIsMarked = new bool[count];
	memset(regionIsMarked, 0, count);
	/* 存储一个区域的最小高度位置、最大高度位置、最小宽度位置、最大宽度位置*/
	int ** markRange = new int *[count];
	int * temp = new int[4 * count];
	for (int t = 0; t < 4; ++t)
		markRange[t] = temp + t*count*sizeof(int);
	//
	int height = img.rows;
	int width = img.cols;
	int i, j, index;
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			index = *(img.data + img.step[1] * i + img.step[2] * j);
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
		rect = new Rect(markRange[0][i], markRange[2][i], markRange[1][i] - markRange[0][i] + 1, width = markRange[3][i] - markRange[2][i] + 1);
		rects.push_back(rect);
	}
	//
	delete[] temp;
	delete[] markRange;
	delete[] regionIsMarked;
	return rects;
}

/*
分割一幅大图像为众多小图元，大图像为类OriginalImage的私有变量
小图元以对象指针的list形式返回
*/
vector<ImagePatch*> OriginalImage::segmentImage() const
{
	Mat preImg(pOImage->rows, pOImage->cols, CV_8UC3);
	preImg = prePareImage(*pOImage, preImg);
	int count = 0;
	vector<ImagePatch*> result;
	//

	//
	vector<Rect *> rects;
	rects = getMetaInfos(preImg, rects, count);
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