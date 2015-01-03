//
//  jz_segment_image.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/1.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#include "egbis_segment_image.h"
#include <cstdlib>
#include <map>

#include "filter.h"
#include "segment-graph.h"
#include "image_convert.h"
#include "tools.h"


// dissimilarity measure between pixels
static inline float diff(image<float> *r, image<float> *g, image<float> *b,
                         int x1, int y1, int x2, int y2) {
    return sqrt(square(imRef(r, x1, y1)-imRef(r, x2, y2)) +
                square(imRef(g, x1, y1)-imRef(g, x2, y2)) +
                square(imRef(b, x1, y1)-imRef(b, x2, y2)));
}

Mat egbis_segment_image(const Mat &m,Mat &retColorMat,int *num_ccs, float sigma, float c, int min_size){
    image<rgb> *nativeImage = convertMatToNativeImage(&m);
    Mat retMat = egbis_segment_image(nativeImage, retColorMat, num_ccs,sigma,c,min_size);
    delete nativeImage;
    return retMat;
}

/*
 * Segment an image
 */


Mat egbis_segment_image(image<rgb> *im, Mat &retColorMat,int *num_ccs, float sigma, float c, int min_size){
    int width = im->width();//cols number
    int height = im->height();//rows number
    
    image<float> *r = new image<float>(width, height);
    image<float> *g = new image<float>(width, height);
    image<float> *b = new image<float>(width, height);
    
    // smooth each color channel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            imRef(r, x, y) = imRef(im, x, y).r;
            imRef(g, x, y) = imRef(im, x, y).g;
            imRef(b, x, y) = imRef(im, x, y).b;
        }
    }
    image<float> *smooth_r = smooth(r, sigma);
    image<float> *smooth_g = smooth(g, sigma);
    image<float> *smooth_b = smooth(b, sigma);
    delete r;
    delete g;
    delete b;
    
    // build graph
    edge *edges = new edge[width*height*4];
    int num = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x < width-1) {
                edges[num].a = y * width + x;
                edges[num].b = y * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y);
                num++;
            }
            
            if (y < height-1) {
                edges[num].a = y * width + x;
                edges[num].b = (y+1) * width + x;
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x, y+1);
                num++;
            }
            
            if ((x < width-1) && (y < height-1)) {
                edges[num].a = y * width + x;
                edges[num].b = (y+1) * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y+1);
                num++;
            }
            
            if ((x < width-1) && (y > 0)) {
                edges[num].a = y * width + x;
                edges[num].b = (y-1) * width + (x+1);
                edges[num].w = diff(smooth_r, smooth_g, smooth_b, x, y, x+1, y-1);
                num++;
            }
        }
    }
    delete smooth_r;
    delete smooth_g;
    delete smooth_b;
    
    // segment
    universe *u = segment_graph(width*height, num, edges, c);
    
    // post process small components
    for (int i = 0; i < num; i++) {
        int a = u->find(edges[i].a);
        int b = u->find(edges[i].b);
        if ((a != b) && ((u->size(a) < min_size) || (u->size(b) < min_size)))
            u->join(a, b);
    }
    delete [] edges;
    *num_ccs = u->num_sets();
    
    Mat retMat = Mat::zeros(height, width, CV_16UC1);
//    tool_print_mat_info(retMat);
    map<int, int> index_map;
    map<int, int>::iterator it;
    int comp_index,color_index = 0;
    int cur_color;
    for (uint y = 0; y < height; y++) {
        for (uint x = 0; x < width; x++) {
            comp_index = u->find(y * width + x);
            if( index_map.count(comp_index) == 0){
                cur_color = color_index;
                index_map[comp_index] = color_index++;
            }else{
                cur_color = index_map[comp_index];
            }
            //TODO : has Problem here?No right now!
            // y is row index and x is col index
            //http://stackoverflow.com/questions/22668409/accessing-elements-of-opencv-mat-cv-16uc1
            retMat.at<ushort>(y,x) = cur_color;
//            *(retMat.data + (y * width + x)) = cur_color;
        }
    }
    
    /*-----------------For Showing segment result start--------------------*/
    retColorMat = Mat::zeros(height,width, CV_8UC3);
    rgb *colors = new rgb[width*height];
    for (int i = 0; i < width*height; i++)
        colors[i] = random_rgb();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int comp = u->find(y * width + x);
            retColorMat.at<Vec3b>(y,x)[0] = colors[comp].b;
            retColorMat.at<Vec3b>(y,x)[1] = colors[comp].g;
            retColorMat.at<Vec3b>(y,x)[2] = colors[comp].r;
        }
    }
    delete [] colors;
    /*-----------------For Showing segment result end--------------------*/
    
    delete u;
    return retMat;
}

