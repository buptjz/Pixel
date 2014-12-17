//
//  removeDuplicatePatchs.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef Xcode_Pixel_Proj_removeDuplicatePatchs_h
#define Xcode_Pixel_Proj_removeDuplicatePatchs_h

#include "patch.h"
#include "originalImage.h"
#include "imagePatch.h"
#include "superImagePatch.h"

#include<iostream>
#include<string.h>
#include<cv.h>
#include<vector>

using namespace cv;
using namespace std;

vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >&,bool);
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >&);
vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>&);

#endif
