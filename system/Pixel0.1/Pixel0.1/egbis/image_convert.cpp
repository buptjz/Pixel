//
//  image_convert.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/1.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#include "image_convert.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "image_convert.h"

using namespace cv;
using namespace std;

/*
 OpenCV C++ Wrapper using the Mat class
 */
image<rgb>* convertMatToNativeImage(const Mat *input){
    int w = input->cols;//width
    int h = input->rows;//height
    image<rgb> *im = new image<rgb>(w,h);
    
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            rgb curr;
            Vec3b intensity = input->at<Vec3b>(i,j);
            curr.b = intensity.val[0];
            curr.g = intensity.val[1];
            curr.r = intensity.val[2];
            //            cout<< i+j*w << " ";
            im->data[j+i*w] = curr;
            //            im->data[i * w +j] = curr;
        }
    }
    return im;
}


Mat convertNativeToMat(image<rgb>* input){
    int w = input->width();
    int h = input->height();
    Mat output(Size(w,h),CV_8UC3);
    
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            rgb curr = input->data[j+i*w];
            //            rgb curr = input->data[i * w +j];
            output.at<Vec3b>(i,j)[0] = curr.b;
            output.at<Vec3b>(i,j)[1] = curr.g;
            output.at<Vec3b>(i,j)[2] = curr.r;
        }
    }
    
    return output;
}

///*
// Typical parameters are sigma = 0.5, k = 500, min = 20.
// Larger values for k result in larger components in the result.
// */
//Mat runEgbisOnMat(int *numccs,Mat *input, float sigma=0.5, float k=500, int min_size=20) {
//    int w = input->cols;
//    int h = input->rows;
//    Mat output(Size(w,h),CV_8UC3);
//
//    // 1. Convert to native format
//    image<rgb> *nativeImage = convertMatToNativeImage(input);
//    // 2. Run egbis algoritm
//    image<rgb> *segmentetImage = segment_image(nativeImage, sigma, k, min_size, numccs);
//    // 3. Convert back to Mat format
//    output = convertNativeToMat(segmentetImage);
//
//    return output;
//}


