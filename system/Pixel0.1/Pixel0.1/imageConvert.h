#ifndef IMAGECONVERT_H
#define IMAGECONVERT_H
#include <QtWidgets/QMainWindow>
#include <highgui.h>
#include <opencv.hpp>

QImage Mat2QImage(cv::Mat &inMat);
cv::Mat QImage2Mat(QImage const& inImage);

#endif