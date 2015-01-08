#include "qt_pixel_main.h"
#include <QtWidgets/QApplication>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "init.h"
#include "logDisplay.h"
extern LogDisplay* logDisplay;

using namespace cv;
int main(int argc, char *argv[])
{
	
	//Params::top_k =5;
	//Params::patch_pixel_min=0.01;
	//Params::shape_context_compare_1_thres = 0.2;
	//Params::shape_context_compare_2_thres = 0.2;
	//Params::featureType_for_one_image = Params::SURF;//featureType used 
	//Params::featureType_for_batch_image = Params::SURF;
	//Params::featureType_for_search = Params::SURF;
	
	init();
	QApplication a(argc, argv);
	qt_Pixel_Main w;
	w.show();
	return a.exec();
	return a.exec();
}
