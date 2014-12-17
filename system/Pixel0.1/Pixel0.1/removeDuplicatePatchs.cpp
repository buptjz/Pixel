#include "tools.h"
#include "removeDuplicatePatchs.h"

//shape context compare
//similar score <= this threshold will be regarded as the same images
static const double SHAPE_CONTEXT_COMPARE_FIRST_THRES = 1.0;
static const double SHAPE_CONTEXT_COMPARE_SECOND_THRES = 2.0;

//Strategy 1:
//vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec){
//    vector<SuperImagePatch *> result;
//    bool find_similar ;
//    for (int i = 0 ; i < patch_vec.size(); i++) {
//        find_similar = false;
//        ImagePatch *one_patch = patch_vec[i];
//        vector<double> scores = one_patch->patchCompareWith(result, "SHAPE_CONTEXT");
//        
//        for (int j = 0; j < result.size(); j++) {
//            SuperImagePatch *tmp_sp = result[j];
//            double score = one_patch->patchCompareWith(tmp_sp, "SHAPE_CONTEXT");
//            // (1) has similar 'SP', insert
//            cout<<score<<endl;
//            if(score <= SHAPE_CONTEXT_COMPARE_FIRST_THRES){
//                vector<Patch *> patch_vec = tmp_sp->getPatchvector();
//                patch_vec.push_back(one_patch);
//                tmp_sp->setPatchList(patch_vec);
//                find_similar = true;
//                break;
//            }
//        }
//        
//        if (!find_similar) {
//            // (2) no similar 'SP', generate a new one
//            Mat *_bsip = new Mat(one_patch->getBinaryImagePatch()->clone());
//            Mat *_osip = new Mat(one_patch->getOriginalImagePatch()->clone());
//            SuperImagePatch *new_sip = new SuperImagePatch("",_bsip,_osip);
//            vector<Patch*> patch_vec = (vector<Patch*> )new_sip->getPatchvector();
//            patch_vec.push_back(one_patch);
//            new_sip->setPatchList(patch_vec);
//            result.push_back(new_sip);
//        }
//    }
//    return result;
//}

//Strategy 2:
vector<SuperImagePatch*> removeDuplicateImagePatch1To1(vector<ImagePatch* >& patch_vec){
    vector<SuperImagePatch *> result;
    bool find_similar ;
    for (int i = 0 ; i < patch_vec.size(); i++) {
        find_similar = false;
        ImagePatch *one_patch = patch_vec[i];
        for (int j = 0; j < result.size(); j++) {
            SuperImagePatch *tmp_sp = result[j];
            double score = one_patch->patchCompareWith(tmp_sp, "SHAPE_CONTEXT");
            // (1) has similar 'SP', insert
            cout<<score<<endl;
            if(score <= SHAPE_CONTEXT_COMPARE_FIRST_THRES){
                vector<Patch *> patch_vec = tmp_sp->getPatchvector();
                patch_vec.push_back(one_patch);
                tmp_sp->setPatchList(patch_vec);
                find_similar = true;
                break;
            }
        }
        
        if (!find_similar) {
            // (2) no similar 'SP', generate a new one
            Mat *_bsip = new Mat(one_patch->getBinaryImagePatch()->clone());
            Mat *_osip = new Mat(one_patch->getOriginalImagePatch()->clone());
            SuperImagePatch *new_sip = new SuperImagePatch("",_bsip,_osip);
            vector<Patch*> patch_vec = (vector<Patch*> )new_sip->getPatchvector();
            patch_vec.push_back(one_patch);
            new_sip->setPatchList(patch_vec);
            result.push_back(new_sip);
        }
    }
	return result;
}


/*
 Remove duplicate image patches in one images
 input  : all patchs in segmented image
 output : a list of super patches
 
 [1] 1 To Many Strategy:
 For each patch 'P', compare it with every super patch 'SP' in super_patches_vector
 if the nearst 'SP'  has similarity('P','SP') <= threshold, insert 'P' to 'SP'
 else, create a new 'SP' with 'P'.
 
 [2] 1 To 1 Strategy:
 once find a pair of 'P' and 'SP' has similarity <= threshold, insert 'P' to 'SP'
 */
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec,bool use1To1){
    if (use1To1) return removeDuplicateImagePatch1To1(patch_vec);
    else return removeDuplicateImagePatchs(patch_vec);
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

