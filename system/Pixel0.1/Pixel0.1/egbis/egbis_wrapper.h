//
//  egbis.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/31.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef Xcode_Pixel_Proj_egbis_h
#define Xcode_Pixel_Proj_egbis_h
#include <opencv2/core/core.hpp>
/*
 Implementation of the segmentation algorithm described in:
 
 Efficient Graph-Based Image Segmentation
 Pedro F. Felzenszwalb and Daniel P. Huttenlocher
 International Journal of Computer Vision, 59(2) September 2004.
 
 sigma: Used to smooth the input image before segmenting it.
 k: Value for the threshold function.
 min: Minimum component size enforced by post-processing.
 input: Input image.
 output: Output image.
 
 Typical parameters are sigma = 0.5, k = 500, min = 20.
 Larger values for k result in larger components in the result.
 */
//Mat runEgbisOnMat(int *,Mat *, float, float, int);
Mat runEgbisOnMat(int *numccs,Mat *input, float sigma=0.5, float k=500, int min_size=20);

#endif
