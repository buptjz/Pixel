/*
 Wang Jizhe main function 
 2014.12.20
 */

#include <iostream>
#include "superImagePatch.h"
#include "imagePatch.h"
#include "originalImage.h"
#include <string>
#include <highgui.h>
#include <cv.h>
#include <stdlib.h>
#include <opencv.hpp>
#include "tools.h"
#include "removeDuplicatePatchs.h"
#include "opencv2/core/core.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include "surfMatch.h"

using namespace std;
using namespace cv;

int main(int agrc, char **agrv){
//    test_surf_match_func();

    vector<ImagePatch*> all_patch;
    string root = "/Volumes/BigData/Pixel/data/ordered/";
    for (int i = 1; i < 4; i++) {
        string c_image_name = root + to_string(i) + "c.jpg";
        string b_image_name = root + to_string(i) + ".jpg";
        Mat cimg = imread(c_image_name,CV_32F);//32-bit RGB image
        Mat bimg = imread(b_image_name,CV_8UC1);//8-bit Black-White image
        
        surf_match_func(cimg,bimg);
        Mat *c = new Mat(cimg);
        Mat *b = new Mat(bimg);
        Rect rect = Rect();
        ImagePatch *ip = new ImagePatch(" ", nullptr, rect, b, c);
        all_patch.push_back(ip);
//        tool_show_mat(bimg, b_image_name);
//        tool_show_mat(cimg, c_image_name);
    }
    
    vector<SuperImagePatch*> fsip = removeDuplicateImagePatchs(all_patch);
    return 0;
}

