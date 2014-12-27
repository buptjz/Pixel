//
//  surfMatch.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/21.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "surfMatch.h"
#include "params.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

struct SURFDetector{
    Ptr<Feature2D> surf;
    SURFDetector(double hessian = 800.0){
        surf = SURF::create(hessian);
    }
    template<class T>
    void operator()(const T& in, const T& mask, std::vector<cv::KeyPoint>& pts, T& descriptors, bool useProvided = false){
        surf->detectAndCompute(in, mask, pts, descriptors, useProvided);
    }
};

//Still has bugs ,abort
///*
// Convert vector<double> to surf descriptors mat
// */
//
//static Mat double_vec2surf_desp_mat(const vector<double> &vec){
//    int cols = Params::surf_dimensions;
//    int rows = (int)vec.size() / Params::surf_dimensions;
//    
//    Mat ret_M(rows,cols,CV_32FC1);
//    
//    size_t eSiz = ret_M.elemSize();
//    size_t total_size = cols * rows* 1 * eSiz;
//    
//    int ind = 0;
//    for (size_t i = 0; i < total_size; i += eSiz){
//        double* tmp = (double *)ret_M.data + i;
//        *tmp = vec[ind++];
//    }
//    cout<<ret_M.elemSize();
//    return ret_M;
//}

///*
// Convert surf descriptors Mat to vector<double>
// http://answers.opencv.org/question/8873/best-way-to-store-a-mat-object-in-android/
// */
//static vector<double> surf_desp_mat2double_vec(const Mat &M){
//    vector<double> ret_vec;
//    if (M.cols == 0 || M.rows == 0)
//        return ret_vec;
//    
//    int cols = M.cols;
//    int rows = M.rows;
//    int chan = M.channels();
//    size_t eSiz = M.elemSize();
//    size_t total_size = cols * rows * chan * eSiz;
//    
//    if (M.isContinuous()){
//        for (size_t i = 0; i < total_size; i += eSiz)
//            ret_vec.push_back(double(*(M.data+i)));
//    }else{
//        cout << "[surf_desp_mat2double_vec] Mat is not continuous!";
//    }
//    return ret_vec;
//}

/*
 get surf descriptors from an image mat
 */
void generate_surf_descriptors(const Mat &img, Mat &ret_descriptors){
    vector<KeyPoint> keypoints;
    SURFDetector surf;
    surf(img, Mat(), keypoints, ret_descriptors);
}

/*
 get surf double vector descriptors from an image mat
 */
void generate_surf_descriptors(const Mat &img, vector<double> &ret_vec){
    Mat descriptors;
    generate_surf_descriptors(img,descriptors);
    cout<<"end"<<endl;
}


/*
 References:
 http://blog.csdn.net/panda1234lee/article/details/10896099
 http://docs.opencv.org/trunk/doc/py_tutorials/py_feature2d/py_matcher/py_matcher.html
 http://stackoverflow.com/questions/21406182/opencv-saving-image-keypoints-and-descriptors-to-file
 */

/*
 Return matching score by surf algorithm with two descriptors' vectors
 */
double surf_match_score_with_descriptor(const Mat &desp1, const Mat &desp2){
    BFMatcher matcher;//Can also try FlannBasedMatcher
    vector< DMatch > matches;
    vector<vector<DMatch>> m_knnMatches;
    
    matches.clear();
    matcher.knnMatch(desp1, desp2, m_knnMatches,2);
    
    //nearest desp >> second nearest desp will be regarded as good matching
    for (int i=0; i<m_knnMatches.size(); i++){
        const DMatch& bestMatch = m_knnMatches[i][0];
        const DMatch& betterMatch = m_knnMatches[i][1];
        float distanceRatio = bestMatch.distance / betterMatch.distance;
        
        if (distanceRatio < Params::surf_min_ratio)
            matches.push_back(bestMatch);
    }
    
    if(!matches.size())
        cout<<"matches is empty! "<<endl;

    return double(matches.size());
}

/*
 Return matching score by surf algorithm with two Images Mats
 */
double surf_match_score_with_mat(const Mat &img1,const Mat &img2){
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    SURFDetector surf;
    surf(img1, Mat(), keypoints1, descriptors1);
    surf(img2, Mat(), keypoints2, descriptors2);
    

    /*-----------DEBUG START ----------*/    
    BFMatcher matcher;
    vector<DMatch> matches;
    Mat img_matched;
    matcher.match(descriptors1, descriptors2, matches);
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matched, Scalar(255,255,255));
    imshow("surf_Matches",img_matched);//显示的标题为Matches
    waitKey(0);
    return 0;
    /*-----------DEBUG END ----------*/
    
    return surf_match_score_with_descriptor(descriptors1, descriptors2);
}

void test_surf_match_func(){
    //    test_descriptor();
    string root = "/Volumes/BigData/Pixel/data/ordered/";
    string left_image_name = root + "1.jpg";
    string right_image_name = root + "2.jpg";
    Mat l_img = imread(left_image_name,CV_8UC1);//32-bit RGB image
    Mat r_img = imread(right_image_name,CV_8UC1);//8-bit Black-White image
    cout<<surf_match_score_with_mat(l_img,r_img)<<endl;
}



