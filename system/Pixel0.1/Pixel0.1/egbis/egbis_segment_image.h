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

Mat egbis_segment_image(image<rgb> *im,int *num_ccs, float sigma=0.5, float c=500, int min_size=20);

/*
 * Segment an image
 *
 * Returns a color image representing the segmentation.
 *
 * im: image to segment.
 * sigma: to smooth the image.
 * c: constant for treshold function.
 * min_size: minimum component size (enforced by post-processing stage).
 * num_ccs: number of connected components in the segmentation.
 */
Mat egbis_segment_image(const Mat &m,int *num_ccs, float sigma=0.5, float c=500, int min_size=20);

#endif /* defined(__Xcode_Pixel_Proj__jz_segment_image__) */
