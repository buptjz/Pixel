#include "tools.h"
#include "removeDuplicatePatchs.h"

/*
 find the smallest element(with its index) in vectors
 */
static void find_nearest(vector<double> &scores, double *score,int *index){
    if (scores.empty()) {
        return;
    }
    
    *score = scores[0];
    *index = 0;
    for(int i = 1; i < (int)scores.size(); i++){
        if (scores[i] < *score){
            *score = scores[i];
            *index = i;
        }
    }
}

/*
 generate a super_patch pointer from image_patch pointer
 */
static SuperImagePatch* generate_super_from_patch(Patch *patch){
    if (patch == nullptr) {
        return nullptr;
    }
    
    Mat *_bsip = new Mat(patch->getBinaryImagePatch()->clone());
    Mat *_osip = new Mat(patch->getOriginalImagePatch()->clone());
    string patch_id = super_patch_id_from_timestamp();
    cout<<"generate super patch id : "<<patch_id<<endl;//debug
    SuperImagePatch *new_sip = new SuperImagePatch(patch_id,_bsip,_osip);
    vector<Patch*> patch_vec = (vector<Patch*> )new_sip->getPatchvector();
    patch_vec.push_back(patch);
    new_sip->setPatchList(patch_vec);
    return new_sip;
}

/*
 Strategy [1]: 1 to many
 */
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec){
    vector<SuperImagePatch *> supers;
    if (patch_vec.empty()) {
        return supers;
    }
    
    // init supers with the first image_patch
    supers.push_back(generate_super_from_patch(patch_vec[0]));
    
    double nearest_score = 0.0;
    int nearest_index = -1;
    for (size_t i = 1; i < patch_vec.size(); i++) {
        ImagePatch *one_patch = patch_vec[i];
        //convert first ,use second
        vector<Patch *> base_patch_vec = convert_verctor<Patch,SuperImagePatch>(supers);
        vector<double> scores = one_patch->patchCompareWith(base_patch_vec, Params::SHAPE_CONTEXT);
        
        find_nearest(scores, &nearest_score, &nearest_index);
        
        //(1) has similar 'SP', insert 'P' to 'SP'
        if (nearest_score <= Params::shape_context_compare_1_thres) {
            vector<Patch *> patch_vec = supers[nearest_index]->getPatchvector();
            patch_vec.push_back(one_patch);
            supers[nearest_index]->setPatchList(patch_vec);
        }else{
        // (2) no similar 'SP', generate a new one
            supers.push_back(generate_super_from_patch(one_patch));
        }
    }
    return supers;
}

/*
 Strategy 2: 1 to 1 comparison
 */
vector<SuperImagePatch*> removeDuplicateImagePatch1To1(vector<ImagePatch* >& patch_vec){
    vector<SuperImagePatch *> result;
    bool find_similar ;
    for (size_t i = 0 ; i < patch_vec.size(); i++) {
        find_similar = false;
        ImagePatch *one_patch = patch_vec[i];
        for (size_t j = 0; j < result.size(); j++) {
            SuperImagePatch *tmp_sp = result[j];
            double score = one_patch->patchCompareWith(tmp_sp, Params::SHAPE_CONTEXT);
            // (1) has similar 'SP', insert
            cout<<score<<endl;
            if(score <= Params::shape_context_compare_1_thres){
                vector<Patch *> patch_vec = tmp_sp->getPatchvector();
                patch_vec.push_back(one_patch);
                tmp_sp->setPatchList(patch_vec);
                find_similar = true;
                break;
            }
        }
        
        if (!find_similar) {
            // (2) no similar 'SP', generate a new one
            result.push_back(generate_super_from_patch(one_patch));
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
    if (use1To1)
        return removeDuplicateImagePatch1To1(patch_vec);
    else
        return removeDuplicateImagePatchs(patch_vec);
}


/*
 second remove duplcate
 input  : super patches
 output : final super patches
 
 Same idea as removeDuplicateImagePatchs
 */

vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>& sp_vec){
    vector<SuperImagePatch*> final_sps;
    
    if (sp_vec.empty()) {
        return final_sps;
    }
    
    //init with the first one
    final_sps.push_back(generate_super_from_patch(sp_vec[0]));
    
    //compare each one in sp_vec to final_supers_vector
    double nearest_score = 0.0;
    int nearest_index = -1;
    for (size_t i = 1; i < sp_vec.size(); i++) {
        SuperImagePatch *candi_sp = sp_vec[i];
        
        vector<Patch *> base = convert_verctor<Patch,SuperImagePatch>(final_sps);
        vector<double> scores = candi_sp->patchCompareWith(base, Params::SHAPE_CONTEXT);

        find_nearest(scores, &nearest_score, &nearest_index);
        //(1) has similar 'SP', merge two 'SP's
        if (nearest_score <= Params::shape_context_compare_1_thres) {
            vector<Patch *>v1 = final_sps[nearest_index]->getPatchvector();
            vector<Patch *>v2 = candi_sp->getPatchvector();
            v1.insert(v1.end(), v2.begin(), v2.end());
            final_sps[nearest_index]->setPatchList(v1);
        }else{
        // (2) no similar 'SP', generate a new one from current 'SP'
            final_sps.push_back(generate_super_from_patch(candi_sp));
        }
    }
    return final_sps;
}

//1 to 1 strategy
//vector<SuperImagePatch*> removeDuplicateSuperImagePatchs(vector<SuperImagePatch*>& sp_vec){
//	vector<SuperImagePatch*> result;
//    for (int i = 0; i < sp_vec.size(); i++) {
//        SuperImagePatch *candi_sp = sp_vec[i];
//        
//        for (int j = 0; j < result.size(); j++) {
//            SuperImagePatch *final_sp = result[j];
//            double score = candi_sp->patchCompareWith(final_sp, "shape_context");
//            // (1) has similar 'SP', insert
//            if(score <= SHAPE_CONTEXT_COMPARE_SECOND_THRES){
//                //merge 2 patch vec
//                vector<Patch *>v1 = final_sp->getPatchvector();
//                vector<Patch *>v2 = candi_sp->getPatchvector();
//                v1.insert(v1.end(), v2.begin(), v2.end());
//                final_sp->setPatchList(v1);
//                break;
//            }
//            // (2) no similar 'SP', generate a new one
//            Mat *_bsip = new Mat(candi_sp->getBinaryImagePatch()->clone());
//            Mat *_osip = new Mat(candi_sp->getOriginalImagePatch()->clone());
//            SuperImagePatch *new_sip = new SuperImagePatch(nullptr,_bsip,_osip);
//            new_sip->setPatchList(candi_sp->getPatchvector());
//            result.push_back(new_sip);
//        }
//    }
//	return result;
//}

