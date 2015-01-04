//
//  xmlHelper.cpp
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/4.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#include "xmlHelper.h"
#include "tinyxml.h"
#include "params.h"
#include <iostream>

void load_params(const string &file){
    TiXmlDocument doc(file.c_str());
    if (!doc.LoadFile()) return;
    
    TiXmlHandle hDoc(&doc);
    TiXmlElement *pElem;
    TiXmlHandle hRoot(0);

    // block: name
    {
        pElem=hDoc.FirstChildElement().Element();
        // should always have a valid root but handle gracefully if it does
        if (!pElem) return;
        cout << pElem->Value();
        // save this for later
        hRoot=TiXmlHandle(pElem);
    }
    
    //------- Group 1 image--------
    pElem = hRoot.FirstChild("image").Element();
    Params::color_image_type = atoi(pElem->FirstChild("color_image_type")->ToElement()->GetText());
    Params::color_image_channels = atoi(pElem->FirstChild("color_image_channels")->ToElement()->GetText());
    Params::grey_image_type = atoi(pElem->FirstChild("grey_image_type")->ToElement()->GetText());
    Params::grey_image_channels = atoi(pElem->FirstChild("grey_image_channels")->ToElement()->GetText());
    Params::connect_map_type = atoi(pElem->FirstChild("connect_map_type")->ToElement()->GetText());
    
    //------- Group 2 segment--------
    pElem = hRoot.FirstChild("segment").Element();
    Params::patch_pixel_min = atof(pElem->FirstChild("patch_pixel_min")->ToElement()->GetText());
    Params::patch_pixel_max = atof(pElem->FirstChild("patch_pixel_max")->ToElement()->GetText());
    Params::egbis_sigma = atof(pElem->FirstChild("egbis_sigma")->ToElement()->GetText());
    Params::egbis_c = atof(pElem->FirstChild("egbis_c")->ToElement()->GetText());
    Params::egbis_min_size = atoi(pElem->FirstChild("egbis_min_size")->ToElement()->GetText());
    
    //------- Group 3 segment--------
    pElem = hRoot.FirstChild("match").Element();
    Params::shape_context_sample_point_num = atoi(pElem->FirstChild("shape_context_sample_point_num")->ToElement()->GetText());
    Params::shape_context_bending_weight = atof(pElem->FirstChild("shape_context_bending_weight")->ToElement()->GetText());
    Params::shape_context_match_weight = atof(pElem->FirstChild("shape_context_match_weight")->ToElement()->GetText());
    Params::shape_context_appearance_weight = atof(pElem->FirstChild("shape_context_appearance_weight")->ToElement()->GetText());
    Params::shape_context_use_rotation = atoi(pElem->FirstChild("shape_context_use_rotation")->ToElement()->GetText());
    Params::surf_descriptor_min = atoi(pElem->FirstChild("surf_descriptor_min")->ToElement()->GetText());
    

    //------- Group 3 segment--------
    //shape context compare
    //similar score <= this threshold will be regarded as the same images
    pElem = hRoot.FirstChild("compare").Element();
    Params::shape_context_compare_1_thres = atof(pElem->FirstChild("shape_context_compare_1_thres")->ToElement()->GetText());
    Params::shape_context_compare_2_thres = atof(pElem->FirstChild("shape_context_compare_2_thres")->ToElement()->GetText());
    Params::surf_compare_1_thres = atof(pElem->FirstChild("surf_compare_1_thres")->ToElement()->GetText());
    Params::surf_compare_2_thres = atof(pElem->FirstChild("surf_compare_2_thres")->ToElement()->GetText());
}


void save_params(const string &file_name){
    TiXmlDocument doc;
    TiXmlElement *ele;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","","");
    doc.LinkEndChild(decl);
    
    TiXmlElement *root = new TiXmlElement("root");
    doc.LinkEndChild(root);
    
    TiXmlComment *comment = new TiXmlComment();
    comment->SetValue("Settings for Algorithm Parameters");
    root->LinkEndChild(comment);
    
    //----- Group 1 -------
    TiXmlElement *group = new TiXmlElement("image");
    root->LinkEndChild(group);
    ele = new TiXmlElement("color_image_type");
    ele->LinkEndChild(new TiXmlText(to_string(Params::color_image_type).c_str()));
    group->LinkEndChild(ele);

    ele = new TiXmlElement("color_image_channels");
    ele->LinkEndChild(new TiXmlText(to_string(Params::color_image_channels).c_str()));
    group->LinkEndChild(ele);

    ele = new TiXmlElement("grey_image_type");
    ele->LinkEndChild(new TiXmlText(to_string(Params::grey_image_type).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("grey_image_channels");
    ele->LinkEndChild(new TiXmlText(to_string(Params::grey_image_channels).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("connect_map_type");
    ele->LinkEndChild(new TiXmlText(to_string(Params::connect_map_type).c_str()));
    group->LinkEndChild(ele);

    
    //----- Group 2 -------
    group = new TiXmlElement("segment");
    root->LinkEndChild(group);
    ele = new TiXmlElement("patch_pixel_min");
    ele->LinkEndChild(new TiXmlText(to_string(Params::patch_pixel_min).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("patch_pixel_max");
    ele->LinkEndChild(new TiXmlText(to_string(Params::patch_pixel_max).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("egbis_sigma");
    ele->LinkEndChild(new TiXmlText(to_string(Params::egbis_sigma).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("egbis_c");
    ele->LinkEndChild(new TiXmlText(to_string(Params::egbis_c).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("egbis_min_size");
    ele->LinkEndChild(new TiXmlText(to_string(Params::egbis_min_size).c_str()));
    group->LinkEndChild(ele);
    
    //----- Group 3 Match -------
    group = new TiXmlElement("match");
    root->LinkEndChild(group);
    ele = new TiXmlElement("shape_context_sample_point_num");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_sample_point_num).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("shape_context_bending_weight");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_bending_weight).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("shape_context_match_weight");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_match_weight).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("shape_context_appearance_weight");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_appearance_weight).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("shape_context_use_rotation");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_use_rotation).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("surf_descriptor_min");
    ele->LinkEndChild(new TiXmlText(to_string(Params::surf_descriptor_min).c_str()));
    group->LinkEndChild(ele);
    
    //----- Group 3 Match compare-------
    group = new TiXmlElement("compare");
    root->LinkEndChild(group);
    ele = new TiXmlElement("shape_context_compare_1_thres");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_compare_1_thres).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("shape_context_compare_2_thres");
    ele->LinkEndChild(new TiXmlText(to_string(Params::shape_context_compare_2_thres).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("surf_compare_1_thres");
    ele->LinkEndChild(new TiXmlText(to_string(Params::surf_compare_1_thres).c_str()));
    group->LinkEndChild(ele);
    
    ele = new TiXmlElement("surf_compare_2_thres");
    ele->LinkEndChild(new TiXmlText(to_string(Params::surf_compare_2_thres).c_str()));
    group->LinkEndChild(ele);
    
    doc.SaveFile(file_name.c_str());

}