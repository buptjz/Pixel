/*
 * shape_context.cpp -- Shape context demo for shape matching
 */

#include "opencv2/shape.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    string img_path = "/Volumes/BigData/PixelSetFiles/data/HappyFish.jpg";
    
    Mat query=imread(img_path);
    namedWindow("Image");
    imshow("BEST MATCH", query);
    waitKey(10000);
    return 0;

}
