#include "imagePatch.h"
#include "superImagePatch.h"

//shape context compare
//similar score <= this threshold will be regarded as the same images
static const double SHAPE_CONTEXT_COMPARE_THRES = 1.0;

/*
 Remove duplicate image patches in one images
 input  : all patchs in segmented image
 output : a list of super patches
 
 For each patch 'P', compare it with super patch 'SP' in super_patches_vector
 if similarity('P','SP') <= threshold, insert 'P' to 'SP'
 if no similar 'SP', then create a new 'SP' with 'P'
 */

vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_list){
    vector<SuperImagePatch *> result;
    
//    for (ImagePatch *tmp_p : patch_list){
//        for (SuperImagePatch *tmp_sp : result) {
//            double score = tmp_p->patchCompareWith(*tmp_sp, "shape_context");
//            if(score <= SHAPE_CONTEXT_COMPARE_THRES){
//
//            }
//        }
//    }
//    ImagePatch *tmp = patch_list;
	return result;
}

/*
 second remove duplcate
 input  : super patches
 output : final super patches
 
 Same idea as removeDuplicateImagePatchs
 */
vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>&){
	vector<SuperImagePatch*> result;
	return result;
}

