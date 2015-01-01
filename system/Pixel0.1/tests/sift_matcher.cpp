//
//  sift_matcher.cpp
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

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;
#include <stdio.h>

int sift_func(){
    
    Mat img_1=imread("./image/query.png");//宏定义时CV_LOAD_IMAGE_GRAYSCALE=0，也就是读取灰度图像
    Mat img_2=imread("./image/rs_query.png");//一定要记得这里路径的斜线方向，这与Matlab里面是相反的
    
    if(!img_1.data || !img_2.data)//如果数据为空
    {
        cout<<"opencv error"<<endl;
        return -1;
    }
    cout<<"open right"<<endl;
    
    //第一步，用SIFT算子检测关键点
    
    SiftFeatureDetector detector;//构造函数采用内部默认的
    std::vector<KeyPoint> keypoints_1,keypoints_2;//构造2个专门由点组成的点向量用来存储特征点
    
    detector.detect(img_1,keypoints_1);//将img_1图像中检测到的特征点存储起来放在keypoints_1中
    detector.detect(img_2,keypoints_2);//同理
    
    //在图像中画出特征点
    Mat img_keypoints_1,img_keypoints_2;
    
    drawKeypoints(img_1,keypoints_1,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);//在内存中画出特征点
    drawKeypoints(img_2,keypoints_2,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
    
    imshow("sift_keypoints_1",img_keypoints_1);//显示特征点
    imshow("sift_keypoints_2",img_keypoints_2);
    
    //计算特征向量
    SiftDescriptorExtractor extractor;//定义描述子对象
    
    Mat descriptors_1,descriptors_2;//存放特征向量的矩阵
    
    extractor.compute(img_1,keypoints_1,descriptors_1);//计算特征向量
    extractor.compute(img_2,keypoints_2,descriptors_2);
    //用burte force进行匹配特征向量
    BFMatcher matcher;//定义一个burte force matcher对象
    vector<DMatch>matches;
    matcher.match(descriptors_1,descriptors_2,matches);
    
    //绘制匹配线段
    Mat img_matches;
    drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);//将匹配出来的结果放入内存img_matches中
    
    //显示匹配线段
    imshow("sift_Matches",img_matches);//显示的标题为Matches
    waitKey(0);
    return 0;
}