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
static SuperImagePatch* generate_super_from_imagepatch(ImagePatch *patch){
    if (patch == nullptr) {
        return nullptr;
    }
    
    Mat *_bsip = new Mat(patch->getBinaryImagePatch()->clone());
    Mat *_osip = new Mat(patch->getOriginalImagePatch()->clone());
    
    string time_number = super_patch_id_from_timestamp();
    string sp_id = patch->getOriginalImage()->getOriginalImageId() + "_superImagePatch_" + time_number;
    
    cout<<"generate super patch id : "<<sp_id<<endl;//debug
    
    /*construct super image patch*/
    SuperImagePatch *new_sip = new SuperImagePatch(sp_id,_bsip,_osip);
    
    //set imagepatch pointer
    vector<Patch*> patch_pointer_vec = new_sip->getPatchList();
    patch_pointer_vec.push_back(patch);
    new_sip->setPatchList(patch_pointer_vec);
    
    //set imagepatch id
    vector<string> patch_ids_vec = new_sip->getPatchIdList();
    patch_ids_vec.push_back(patch->getImagePatchId());
    new_sip->setPatchIdList(patch_ids_vec);

    return new_sip;
}

/*
 Strategy [1]: 1 to many
 */
vector<SuperImagePatch*> removeDuplicateImagePatchs(vector<ImagePatch* >& patch_vec){
    cout<<"***************************[Start] Remove Duplicate Image patchs***************************"<<endl;
    vector<SuperImagePatch *> supers;
    if (patch_vec.empty()) {
        return supers;
    }
    
    // init supers with the first image_patch
    supers.push_back(generate_super_from_imagepatch(patch_vec[0]));
    
    double nearest_score = 0.0;
    int nearest_index = -1;
    for (size_t i = 1; i < patch_vec.size(); i++) {
        
        ImagePatch *one_patch = patch_vec[i];
        cout<<"----------------------------------------------------"<<endl;
        cout<<"[Patch="<<one_patch->getImagePatchId()<<"] start searching same"<<endl;
        //convert first ,use second
        vector<Patch *> base_patch_vec = convert_verctor<Patch,SuperImagePatch>(supers);
        vector<double> scores = one_patch->patchCompareWith(base_patch_vec, Params::SHAPE_CONTEXT);
        
        find_nearest(scores, &nearest_score, &nearest_index);
        cout<<"nearest_score = "<<nearest_score;
        //(1) has similar 'SP', insert 'P' to 'SP'
        if (nearest_score <= Params::shape_context_compare_1_thres) {
            cout<<",merge! "<<endl;
            cout<<"The same SuperPatch= "<<supers[nearest_index]->getSuperImagePatchId()<<endl;
            
            //set pointer
            vector<Patch *> patch_vec = supers[nearest_index]->getPatchList();
            patch_vec.push_back(one_patch);
            supers[nearest_index]->setPatchList(patch_vec);
            
            //set ids
            vector<string> patch_ids = supers[nearest_index]->getPatchIdList();
            patch_ids.push_back(one_patch->getImagePatchId());
            supers[nearest_index]->setPatchIdList(patch_ids);
            
        }else{
        // (2) no similar 'SP', generate a new one
            cout<<",generate new one"<<endl;
            supers.push_back(generate_super_from_imagepatch(one_patch));
        }
    }
    cout<<"***************************[End] Remove Duplicate Image patchs***************************"<<endl;
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
                //set pointer
                vector<Patch *> patch_vec = tmp_sp->getPatchList();
                patch_vec.push_back(one_patch);
                tmp_sp->setPatchList(patch_vec);
                
                //set ids
                vector<string> patch_ids = tmp_sp->getPatchIdList();
                patch_ids.push_back(one_patch->getImagePatchId());
                tmp_sp->setPatchIdList(patch_ids);
                
                find_similar = true;
                break;
            }
        }
        
        if (!find_similar) {
            // (2) no similar 'SP', generate a new one
            result.push_back(generate_super_from_imagepatch(one_patch));
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
    cout<<"***************************[Start] Remove Duplicate SuperImage patchs***************************"<<endl;
    vector<SuperImagePatch*> final_sps;
    
    if (sp_vec.empty()) {
        return final_sps;
    }
    
    //init with the first one
    SuperImagePatch *new_super = new SuperImagePatch(*sp_vec[0]);
    final_sps.push_back(new_super);
    
    //compare each one in sp_vec to final_supers_vector
    double nearest_score = 0.0;
    int nearest_index = -1;
    for (size_t i = 1; i < sp_vec.size(); i++) {
        SuperImagePatch *candi_sp = sp_vec[i];
        cout<<"----------------------------------------------------"<<endl;
        cout<<"[SuperPatch="<<candi_sp->getSuperImagePatchId()<<"] start [Filtering]"<<endl;
        vector<Patch *> base = convert_verctor<Patch,SuperImagePatch>(final_sps);
        vector<double> scores = candi_sp->patchCompareWith(base, Params::SHAPE_CONTEXT);

        find_nearest(scores, &nearest_score, &nearest_index);
        //(1) has similar 'SP', merge two 'SP's
        cout<<"nearest_score = "<<nearest_score<<endl;
        if (nearest_score <= Params::shape_context_compare_2_thres) {
            //set pointers
            cout<<"Merge ! Same SuperImagePatch = " <<final_sps[nearest_index]->getSuperImagePatchId()<<endl;
            vector<Patch *>v1 = final_sps[nearest_index]->getPatchList();
            vector<Patch *>v2 = candi_sp->getPatchList();
            v1.insert(v1.end(), v2.begin(), v2.end());
            final_sps[nearest_index]->setPatchList(v1);
            
            //set ids
            vector<string> s1 = final_sps[nearest_index]->getPatchIdList();
            vector<string> s2 = candi_sp->getPatchIdList();
            s1.insert(s1.end(), s2.begin(), s2.end());
            final_sps[nearest_index]->setPatchIdList(s1);
        }else{
        // (2) no similar 'SP', generate a new one from current 'SP'
            SuperImagePatch *new_super = new SuperImagePatch(*candi_sp);
            final_sps.push_back(new_super);
            cout<<"No same, generate new one with superImagePatch id="<<candi_sp->getSuperImagePatchId()<<endl;
        }
    }
    cout<<"***************************[End] Remove Duplicate SuperImage patchs***************************"<<endl;
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

