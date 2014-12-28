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
#include "jsonHelper.h"

using namespace std;
using namespace cv;

int main(int agrc, char **agrv){
//    test_surf_match_func();
    
//    SuperImagePatch sip;
//    giveVGeAPatch("/Volumes/BigData/Pixel/data/ordered/2.jpg",sip);

    vector<ImagePatch*> all_patch;
    string root = "/Volumes/BigData/Pixel/data/ordered/";
//    string img_name = root + "demoLittle.jpg";
    string img_name = root + "demo.jpg";
//    string img_name = root + "demo2.png";
    Mat img = imread(img_name);
    Mat cimg;
//    img.convertTo(cimg, CV_8UC1);
    cvtColor(img, cimg, CV_BGR2GRAY);
//    tool_show_mat(cimg, "before");
    cout <<"type: "<< cimg.type()<<endl;
    cout <<"channels: "<< cimg.channels() << endl;
    cout <<"elemSize: "<< cimg.elemSize() << endl;
    cout <<"depth :" <<cimg.depth() << endl;
    cout << "-----------------" <<endl;
    string str;
    mat2jsonString(cimg, str);
    tool_show_mat(cimg, "before");
    
    Mat after;
    jsonString2Mat(str, after);
    tool_show_mat(after, "after");
//    cout<<str;
    
//    for (int i = 1; i < 4; i++) {
//        string c_image_name = root + to_string(i) + "c.jpg ";
//        string b_image_name = root + to_string(i) + ".jpg";
//        Mat cimg = imread(c_image_name,CV_8UC3);//32-bit RGB image
//        Mat bimg = imread(b_image_name,CV_LOAD_IMAGE_COLOR);//8-bit Black-White image
////        Mat bimg;
////        cimg.convertTo(bimg, CV_8UC3);
//        
////        Mat aaa;
////        generate_surf_descriptors(cimg,aaa);
////        cout<<surf_match_score_with_mat(cimg,bimg)<<endl;
//    
//        Mat *c = new Mat(cimg);
//        Mat *b = new Mat(bimg);
//        Rect rect = Rect();
//        OriginalImage *oi = new OriginalImage("ori" + to_string(i));
//        ImagePatch *ip = new ImagePatch("ori_id", oi, rect, b, c);
//        all_patch.push_back(ip);
//        tool_show_mat(bimg, b_image_name);
//        tool_show_mat(cimg, c_image_name);
//    }
//
//    vector<SuperImagePatch *> fsip = removeDuplicateImagePatchs(all_patch);
//    vector<SuperImagePatch *> fsip_removed = removeDuplicateSuperImagePatchs(fsip);
    return 0;
}

