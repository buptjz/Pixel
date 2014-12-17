#include "tools.h"
#include "removeDuplicatePatchs.h"

//shape context compare
//similar score <= this threshold will be regarded as the same images
static const double SHAPE_CONTEXT_COMPARE_FIRST_THRES = 1.0;
static const double SHAPE_CONTEXT_COMPARE_SECOND_THRES = 2.0;

/*
 Remove duplicate image patches in one images
 input  : all patchs in segmented image
 output : a list of super patches
 
 For each patch 'P', compare it with super patch 'SP' in super_patches_vector
 if similarity('P','SP') <= threshold, insert 'P' to 'SP'
 if no similar 'SP', then create a new 'SP' with 'P'
 */

vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec){

    vector<SuperImagePatch *> result;
    for (int i = 0 ; i < patch_vec.size(); i++) {
        ImagePatch *one_patch = patch_vec[i];
        for (int j = 0; j < result.size(); j++) {
            SuperImagePatch *tmp_sp = result[j];
            double score = one_patch->patchCompareWith(tmp_sp, "shape_context");
            // (1) has similar 'SP', insert
            if(score <= SHAPE_CONTEXT_COMPARE_FIRST_THRES){
                vector<Patch *> patch_vec = tmp_sp->getPatchvector();
                patch_vec.push_back(one_patch);
                tmp_sp->setPatchList(patch_vec);
                break;
            }
        }
        // (2) no similar 'SP', generate a new one
        Mat bsip = one_patch->getBinaryImagePatch()->clone();
        Mat *_osip = new Mat(one_patch->getOriginalImagePatch()->clone());
        SuperImagePatch *new_sip = new SuperImagePatch(nullptr,&bsip,_osip);
        vector<Patch*> patch_vec = (vector<Patch*> )new_sip->getPatchvector();
        patch_vec.push_back(one_patch);
        new_sip->setPatchList(patch_vec);
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

vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>& sp_vec){
	vector<SuperImagePatch*> result;
    for (int i = 0; i < sp_vec.size(); i++) {
        SuperImagePatch *candi_sp = sp_vec[i];
        
        for (int j = 0; j < result.size(); j++) {
            SuperImagePatch *final_sp = result[j];
            double score = candi_sp->patchCompareWith(final_sp, "shape_context");
            // (1) has similar 'SP', insert
            if(score <= SHAPE_CONTEXT_COMPARE_SECOND_THRES){
                //merge 2 patch vec
                vector<Patch *>v1 = final_sp->getPatchvector();
                vector<Patch *>v2 = candi_sp->getPatchvector();
                v1.insert(v1.end(), v2.begin(), v2.end());
                final_sp->setPatchList(v1);
                break;
            }
            // (2) no similar 'SP', generate a new one
            Mat *_bsip = new Mat(candi_sp->getBinaryImagePatch()->clone());
            Mat *_osip = new Mat(candi_sp->getOriginalImagePatch()->clone());
            SuperImagePatch *new_sip = new SuperImagePatch(nullptr,_bsip,_osip);
            new_sip->setPatchList(candi_sp->getPatchvector());
            result.push_back(new_sip);
        }
    }
	return result;
}

