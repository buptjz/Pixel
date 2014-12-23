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

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

struct SURFDetector{
    Ptr<Feature2D> surf;
    SURFDetector(double hessian = 800.0)
    {
        surf = SURF::create(hessian);
    }
    template<class T>
    void operator()(const T& in, const T& mask, std::vector<cv::KeyPoint>& pts, T& descriptors, bool useProvided = false)
    {
        surf->detectAndCompute(in, mask, pts, descriptors, useProvided);
    }
};

//http://blog.csdn.net/panda1234lee/article/details/10896099

int surf_match_func(const Mat &img1,const Mat &img2){
    FlannBasedMatcher matcher;
    vector<vector<DMatch>> m_knnMatches;
    vector< DMatch > matches;
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    SURFDetector surf;
    
    surf(img1, Mat(), keypoints1, descriptors1);
    surf(img2, Mat(), keypoints2, descriptors2);
    
    matches.clear();
    const float minRatio = 1.f / 1.5f;
    matcher.knnMatch(descriptors1, descriptors2, m_knnMatches,2);
    
    for (int i=0; i<m_knnMatches.size(); i++){
        const DMatch& bestMatch = m_knnMatches[i][0];
        const DMatch& betterMatch = m_knnMatches[i][1];
        float distanceRatio = bestMatch.distance / betterMatch.distance;
        if (distanceRatio < minRatio)
            matches.push_back(bestMatch);
    }
    
    if(!matches.size())
        cout<<"matches is empty! "<<endl;
    
    return double(matches.size());
}

void test_surf_match_func(){
    //    test_descriptor();
    string root = "/Volumes/BigData/Pixel/data/ordered/";
    string left_image_name = root + "1.jpg";
    string right_image_name = root + "2.jpg";
    Mat l_img = imread(left_image_name,CV_8UC1);//32-bit RGB image
    Mat r_img = imread(right_image_name,CV_8UC1);//8-bit Black-White image
    surf_match_func(l_img,r_img);
}



