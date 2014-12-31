#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
 OpenCV C++ Wrapper using the Mat class
 */
image<rgb>* convertMatToNativeImage(Mat *input){
    int w = input->cols;
    int h = input->rows;
    image<rgb> *im = new image<rgb>(w,h);

    for(int i=0; i<input->rows; i++)
    {
        for(int j=0; j<input->cols; j++)
        {
            rgb curr;
            Vec3b intensity = input->at<Vec3b>(i,j);
            curr.b = intensity.val[0];
            curr.g = intensity.val[1];
            curr.r = intensity.val[2];
            im->data[i+j*w] = curr;
        }
    }
    return im;
}

Mat convertNativeToMat(image<rgb>* input){
    int w = input->width();
    int h = input->height();
    Mat output(Size(w,h),CV_8UC3);

    for(int i =0; i<w; i++){
        for(int j=0; j<h; j++){
            rgb curr = input->data[i+j*w];
            output.at<Vec3b>(i,j)[0] = curr.b;
            output.at<Vec3b>(i,j)[1] = curr.g;
            output.at<Vec3b>(i,j)[2] = curr.r;
        }
    }

    return output;
}

/*
 Typical parameters are sigma = 0.5, k = 500, min = 20.
 Larger values for k result in larger components in the result.
 */
Mat runEgbisOnMat(Mat *input, float sigma, float k, int min_size, int *numccs) {
    int w = input->cols;
    int h = input->rows;
    Mat output(Size(w,h),CV_8UC3);

    // 1. Convert to native format
    image<rgb> *nativeImage = convertMatToNativeImage(input);
    // 2. Run egbis algoritm
    image<rgb> *segmentetImage = segment_image(nativeImage, sigma, k, min_size, numccs);
    // 3. Convert back to Mat format
    output = convertNativeToMat(segmentetImage);

    return output;
}

int test_egbis(int argc, char **argv) {
    Mat img = imread(argv[1]);
    int num_ccs;
    Mat egbisImage = runEgbisOnMat(&img, 0.5, 500, 200, &num_ccs);
    return 0;
}

