//
//  tools.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include "tools.h"
#include "params.h"
#include <time.h>
#include <ctime>

#ifdef __DEBUG__
#include "logDisplay.h"
extern LogDisplay* logDisplay;
#endif


/*
 Statastic of Running Time
 */
static int64 work_begin = 0;
static int64 work_end = 0;

//calling before running algorithm
void tool_work_begin(){
    work_begin = getTickCount();
}

//calling after running algorithm
void tool_work_end(){
    work_end = getTickCount() - work_begin;
}

//calling after too_work_end to get running time
double tool_get_work_time(){
    return work_end /((double)getTickFrequency() )* 1000.;
}

/*
 convert connected component to color image (for showing while debug)
 */
void connected_component2color_image(const Mat &cc,const int number_of_component, Mat &ret_color_image){
    //generate random colors
    rgb *colors = new rgb[number_of_component];
    for (int i = 0; i < number_of_component; i++)
        colors[i] = random_rgb();
    
    //generate color image
    int height = cc.rows;
    int width = cc.cols;
    ret_color_image = Mat::zeros(height,width, CV_8UC3);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int color_index = cc.at<ushort>(y,x);
            ret_color_image.at<Vec3b>(y,x)[0] = colors[color_index].b;
            ret_color_image.at<Vec3b>(y,x)[1] = colors[color_index].g;
            ret_color_image.at<Vec3b>(y,x)[2] = colors[color_index].r;
        }
    }
    delete [] colors;
}

// generate random RGB color
rgb random_rgb(){
    //http://www.opencv.org.cn/opencvdoc/2.3.2/html/modules/core/doc/operations_on_arrays.html?highlight=rng#RNG
    static RNG rng;
    rgb c;
    c.r = (uchar)rng.uniform(0, 255);
    c.g = (uchar)rng.uniform(0, 255);
    c.b = (uchar)rng.uniform(0, 255);
    return c;
}

//log Mat info
void tool_print_mat_info(Mat M){
#ifdef __DEBUG__
    logDisplay->logDisplay("---------- Mat Info ----------");
    logDisplay->logDisplay("[Cols ] " + to_string(M.cols));
    logDisplay->logDisplay("[Rows ] " + to_string(M.rows));
    logDisplay->logDisplay("[eSize ] " + to_string(M.elemSize()));
    logDisplay->logDisplay("[Chann ] " + to_string(M.channels()));
    logDisplay->logDisplay("[depth ] " + to_string(M.depth()));
    logDisplay->logDisplay("[Conti ] " + to_string(M.isContinuous()));
    logDisplay->logDisplay("[lengt ] " + to_string( M.dataend - M.datastart));
    logDisplay->logDisplay("------------------------------");
#endif
}


void tool_show_patch(Patch *image, string name){
    cv::namedWindow(name);
    cv::imshow(name, *(image->getOriginalImagePatch()));
    cv::waitKey(0);
}

void tool_show_mat(Mat mat,string name){
    cv::namedWindow(name);
    cv::imshow(name, mat);
    cv::waitKey(0);
}


string super_patch_id_from_timestamp(){
    static long long unique_patch_id = 0;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer,80,"%Y%m%d%I%M%S_",timeinfo);
    string str(buffer);
    str += to_string(unique_patch_id);
    unique_patch_id++;

    return str;
}

string getTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d %I:%M:%S", timeinfo);
	string str(buffer);
	return str;
}

Mat imread_and_preprocess(const string& filename)
{
	Mat tmp = imread(filename);
	if(tmp.data == NULL)
		return tmp;
	tmp.convertTo(tmp,Params::color_image_type);
	return tmp;
}


//split string by pattern
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//expand string
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

void drawPatch(Mat& image, const Rect &position)
{
	//Mat image_clone = image.clone();
	int channels = image.channels();

	int x = position.x;
	int y = position.y;
	int height = position.height;
	int width = position.width;

	//rectangle(image, Point(x, y), Point(x + height, y + width), Scalar(0, 255, 255), 1, 8);
	rectangle(image, Point(x, y), Point(x+ width, y + height), Scalar(0, 0, 255), 3, 8);
	namedWindow("image", WINDOW_KEEPRATIO);
	imshow("image", image);

	waitKey(0);
}
