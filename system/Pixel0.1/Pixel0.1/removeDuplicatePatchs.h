//
//  removeDuplicatePatchs.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 14/12/17.
//  Copyright (c) 2014年 WangJZ. All rights reserved.
//

#ifndef Xcode_Pixel_Proj_removeDuplicatePatchs_h
#define Xcode_Pixel_Proj_removeDuplicatePatchs_h

#include "imagePatch.h"
#include "superImagePatch.h"

#include<string.h>
#include<vector>

using namespace std;

/*--------------------------------------
 Interfaces of Remove Duplicate patches
 Supported by JZ
 --------------------------------------*/

/*
 Remove duplicate image patches in one images
 patch_vec : all patchs in segmented image
 use1To1 : use 1 To 1 Strategy or not
 output : a list of super patches
 
 [1] 1 To Many Strategy:
 For each patch 'P', compare it with every super patch 'SP' in super_patches_vector
 if the nearst 'SP'  has similarity('P','SP') <= threshold, insert 'P' to 'SP'
 else, create a new 'SP' with 'P'.
 
 [2] 1 To 1 Strategy:
 once find a pair of 'P' and 'SP' has similarity <= threshold, insert 'P' to 'SP'
 */
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec,bool use1To1);

/*
 Default algorithm of removing duplicate imagePatches
 Strategy [1]: 1 to many
 */
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >&);

/*
 Second loop of  remove duplcate (Remove duplicate super image patches)
 Same idea as removeDuplicateImagePatchs
 input  : super patches
 output : final super patches
 */
vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>&);


//for test
void giveVGeAPatch(string img_path, SuperImagePatch &sip);

#endif
