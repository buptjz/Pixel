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
	init();
	QApplication a(argc, argv);
	qt_Pixel_Main w;
	w.show();
	return a.exec();
	return a.exec();
}
