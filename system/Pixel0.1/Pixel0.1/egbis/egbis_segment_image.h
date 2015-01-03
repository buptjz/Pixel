//
//  jz_segment_image.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/1.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__jz_segment_image__
#define __Xcode_Pixel_Proj__jz_segment_image__

#include <stdio.h>
#include <opencv.hpp>
#include "image.h"
#include "misc.h"

using namespace cv;
using namespace std;

Mat egbis_segment_image(image<rgb> *im,Mat &retColorMat,int *num_ccs, float sigma=0.5, float c=500, int min_size=20);

/*
 * Segment an image
 *
 * Returns a connected component image representing the segmentation.(each component with a particular number)
 *
 * m: image to segment.
 * retColorMat : a CV_8UC3 image,each component with a random color!(For debug)
 * num_ccs: number of connected components in the segmentation.
 * sigma: to smooth the image.
 * c: constant for treshold function.(The bigger c is,the larger each component is.)
 * min_size: minimum component size (enforced by post-processing stage).

 */
Mat egbis_segment_image(const Mat &m, Mat &retColorMat,int *num_ccs, float sigma=0.5, float c=500, int min_size=20);

#endif /* defined(__Xcode_Pixel_Proj__jz_segment_image__) */
