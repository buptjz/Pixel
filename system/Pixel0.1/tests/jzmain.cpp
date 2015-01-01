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
#include "egbis_wrapper.h"
using namespace std;
using namespace cv;

int main(int agrc, char **agrv){
//    test_surf_match_func();

    vector<ImagePatch*> all_patch;
    string root = "/Volumes/BigData/Pixel/data/ordered/";
    Mat ori = imread(root+"demo.jpg",CV_LOAD_IMAGE_COLOR);
    cout << ori.channels() << endl;
    cout << ori.depth() << endl;
    cout << ori.elemSize() << endl;
//    cvtColor(ori, img, );
    int number = 0;
    Mat cimg_seged = runEgbisOnMat(&number,&ori);
//    cout << cimg_seged;
    tool_show_mat(cimg_seged, "segment");
//    
//    for (int i = 1; i < 4; i++) {
//        string c_image_name = root + to_string(i) + "cc.jpg ";
//        string b_image_name = root + to_string(i) + ".jpg";
//        Mat cimg = imread(c_image_name);
//        Mat bimg = imread(b_image_name);
//        
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

