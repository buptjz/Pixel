#include "originalImage.h"
/*
将图片信息存入数据库中
会首先调用数据库的连接，向数据库中写入
图像名（originalImageId）、图像路径(path)
*/
void OriginalImage::saveOriginalImage()
{

}

/*
分割一幅大图像为众多小图元，大图像为类OriginalImage的私有变量
小图元以对象指针的list形式返回
*/
list<ImagePatch*> OriginalImage::segmentImage()
{
	list<ImagePatch*> result;
	return result;
}