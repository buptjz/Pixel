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
    for (ImagePatch *tmp_p : patch_list){
        for (SuperImagePatch *tmp_sp : result) {
            double score = tmp_p->patchCompareWith(tmp_sp, "shape_context");
            //has similar 'SP', insert
            if(score <= SHAPE_CONTEXT_COMPARE_THRES){
                tmp_sp->getPatchvector().push_back(tmp_sp);
                break;
            }
        }
        // no similar 'SP', generate a new one
        Mat *_bsip = new Mat();
        Mat *_osip = new Mat();
        tmp_p->getBinaryImagePatch()->copyTo(*_bsip);
        tmp_p->getOriginalImagePatch()->copyTo(*_osip);
        SuperImagePatch *new_sip = new SuperImagePatch(NULL,_bsip,_osip);
        vector<Patch*> patch_vec = new_sip->getPatchvector();
        patch_vec.push_back(tmp_p);
        result.push_back(new_sip);
    }
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

