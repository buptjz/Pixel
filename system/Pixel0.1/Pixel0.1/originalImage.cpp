//#include "originalImage.h"
///*
//��ͼƬ��Ϣ�������ݿ���
//�����ȵ������ݿ�����ӣ������ݿ���д��
//ͼ������originalImageId����ͼ��·��(path)
//*/
//
///*
//static const Mat & prePareImage(Mat &);
///* ������ͨͼ�� ������������СͼԪ��λ����Ϣ
//CvRect �������:
//CvRect *rects = new CvRect[count]*/
//static vector<Rect *> & getMetaInfos(const Mat &, vector<Rect *> &, int);
//
//OriginalImage::OriginalImage(const string & path, const string & originalImageId)
//{
//	this->originalImageId = originalImageId;
//	this->path = path;
//	pOImage = 0;
//}
//
//OriginalImage::OriginalImage(const string & originalImageId, const string & path, Mat
//	* const pOImage)
//{
//	this->originalImageId = originalImageId;
//	this->path = path;
//	this->pOImage = pOImage;
//}
//
//void OriginalImage::saveOriginalImage() const
//{
//
//}
//
//static vector<Rect *> & getMetaInfos(const Mat & img, vector<Rect *> & rects, int count)
//{
//	/* ��ʶһ�������Ƿ���ʹ�*/
//	bool * regionIsMarked = new bool[count];
//	memset(regionIsMarked, 0, count);
//	/* �洢һ���������С�߶�λ�á����߶�λ�á���С���λ�á������λ��*/
//	int ** markRange = new int *[count];
//	int * temp = new int[4 * count];
//	for (int t = 0; t < 4; ++t)
//		markRange[t] = temp + t*count*sizeof(int);
//	//
//	int height = img.rows;
//	int width = img.cols;
//	int i, j, index;
//	for (i = 0; i < height; ++i)
//	{
//		for (j = 0; j < width; ++j)
//		{
//			index = img.at<int>(i, j);
//			if (index == 0)
//				continue;
//			else if (regionIsMarked[index - 1])
//			{
//				if (markRange[0][index - 1] > i)					markRange[0][index - 1] = i;
//				else if (markRange[1][index - 1] < i)			markRange[1][index - 1] = i;
//				if (markRange[2][index - 1] > j)					markRange[2][index - 1] = j;
//				else if (markRange[3][index - 1] < j)			markRange[3][index - 1] = j;
//			}
//			else
//			{
//				regionIsMarked[index - 1] = true;
//				markRange[0][index - 1] = i;
//				markRange[1][index - 1] = i;
//				markRange[2][index - 1] = j;
//				markRange[3][index - 1] = j;
//			}
//		}
//	}
//	Rect *rect = new Rect();
//	// ��λ����ϢתΪΪRect
//	for (i = 0; i < count; ++i)
//	{
//		rect = new Rect(markRange[0][i], markRange[2][i], markRange[1][i] - markRange[0][i] + 1, width = markRange[3][i] - markRange[2][i] + 1);
//		rects.push_back(rect);		
//	}
//	//
//	delete temp;
//	delete markRange;
//	delete regionIsMarked;
//	return rects;
//}
//
///*
//�ָ�һ����ͼ��Ϊ�ڶ�СͼԪ����ͼ��Ϊ��OriginalImage��˽�б���
//СͼԪ�Զ���ָ���list��ʽ����
//*/
//vector<ImagePatch*> OriginalImage::segmentImage() const
//{
//	Mat preImg(pOImage->rows, pOImage->cols, CV_8UC3);
//	preImg = prePareImage(preImg);
//	int count = 0;
//	vector<ImagePatch*> result;
//	//
//
//	//
//	vector<Rect *> rects;
//	rects = getMetaInfos(preImg, rects, count);
//	//
//	for each (Rect * rect in rects)
//	{
//
//	}
//	return result;
//}
////here is wrong, I changed it
//Mat result;
//const Mat & prePareImage(Mat & img)
//{
//	//Mat result;
//	return result;
//}
