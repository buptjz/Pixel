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

using namespace std;
#include <iostream>

void load_params(const string &file){
    TiXmlDocument doc(file.c_str());
    if (!doc.LoadFile()) return;
    
    TiXmlHandle hDoc(&doc);
    TiXmlElement *pElem;
    TiXmlHandle hRoot(0);
    
    // block: root
    {
        pElem=hDoc.FirstChildElement().Element();
        // should always have a valid root but handle gracefully if it does
        if (!pElem) return;
        // save this for later
        hRoot=TiXmlHandle(pElem);
    }
    
    // block: params dictionary
    {
        pElem = hRoot.FirstChildElement().Element();
        string p_type;
        map<string, pair<string, void*> >::iterator it;
        for(; pElem; pElem = pElem->NextSiblingElement()){
            const char *pKey = pElem->Value();
            const char *pText = pElem->GetText();
            if (pKey && pText){
                it = Params::__attr__.find(pKey);
                if (it != Params::__attr__.end()) {
                    p_type = (it->second).first;
                    if (p_type == "float") {
                        *((float *)((it->second).second)) = atof(pText);
                    }else if(p_type == "double"){
                        *((double *)((it->second).second)) = atof(pText);
                    }else if(p_type == "int"){
                        *((int *)((it->second).second)) = atoi(pText);
                    }else if(p_type == "bool"){
                        *((bool *)((it->second).second)) = (bool) atoi(pText);
                    }else{
                        *((string *)((it->second).second)) = string(pText);
                    }
                }
            }else{
                cout << "[Error] cannot figure the param "<< pKey <<endl;
            }
        }
    }
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
    
    void *p_pointer;
    string p_name,p_type;
    map<string, pair<string, void*>>::iterator it = Params::__attr__.begin();
    for (; it != Params::__attr__.end(); it++) {
        p_name = it->first;
        p_type = (it->second).first;
        p_pointer = (it->second).second;
        
        ele = new TiXmlElement(p_name.c_str());
        if (p_type == "int")
            ele->LinkEndChild(new TiXmlText(to_string(*((int *)p_pointer)).c_str()));
        else if(p_type == "float")
            ele->LinkEndChild(new TiXmlText(to_string(*((float *)p_pointer)).c_str()));
        else if(p_type == "double")
            ele->LinkEndChild(new TiXmlText(to_string(*((double *)p_pointer)).c_str()));
        else if(p_type == "bool")
            ele->LinkEndChild(new TiXmlText(to_string(*((bool *)p_pointer)).c_str()));
        else{
            string s = *(string *)p_pointer;
            ele->LinkEndChild(new TiXmlText(s.c_str()));
        }
        root->LinkEndChild(ele);
    }
    doc.SaveFile(file_name.c_str());
}