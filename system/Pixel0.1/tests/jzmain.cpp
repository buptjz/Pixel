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
#include "egbis_segment_image.h"
#include "xmlHelper.h"
#include "logDisplay.h"

using namespace std;
using namespace cv;

LogDisplay* logDisplay = new LogDisplay();

int main(int agrc, char **agrv){
    string file_name = "params.xml";
    save_params(file_name);
    load_params(file_name);
    save_params("Paras_com.xml");

//    test_surf_match_func();

    vector<ImagePatch*> all_patch;
    string root = "/Volumes/BigData/Pixel/data/pure/";
//    string image = "1/3.TIF";//4000
//    string image = "1/2.TIF";//3000
//    string image = "1/1.TIF";//2000
//    string image = "2/3.jpg";//2000
//    string image = "2/1.jpg";//2000
    string image = "2/2.jpg";//500
//    string image = "3/3.jpg";//2000
    Mat ori = imread(root+image,CV_LOAD_IMAGE_COLOR);
//    tool_print_mat_info(ori);
//    cvtColor(ori, img, );
    int number = 0;
    
    float sigma = 0.5;
    float k = 500;
    int min_size = 200;
//    Mat cimg_seged = runEgbisOnMat(&number,&ori,sigma,k,min_size);
    Mat color_seged;
    Mat cimg_seged = egbis_segment_image(ori,color_seged,&number, sigma,k,min_size);
    cout << "Find " << number << " segments" << endl;
    Mat color;
    
    tool_work_begin();
    connected_component2color_image(cimg_seged, number, color);
    tool_work_end();
    cout<<tool_get_work_time()<<" ms"<<endl;
    
    tool_show_mat(color_seged, "segment");
    tool_show_mat(color, "segment2");
//    tool_print_mat_info(color_seged);
//    tool_show_mat(cimg_seged, "seged");
//    cout << cimg_seged << endl;
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

