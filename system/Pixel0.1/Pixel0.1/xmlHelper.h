//
//  xmlHelper.h
//  Xcode_Pixel_Proj
//
//  Created by WangJZ on 15/1/4.
//  Copyright (c) 2015年 WangJZ. All rights reserved.
//

#ifndef __Xcode_Pixel_Proj__xmlHelper__
#define __Xcode_Pixel_Proj__xmlHelper__

#include <stdio.h>
#include <string>
using namespace std;

/*--------------------------------------
 Interfaces of Load/Save XML Settings
 Supported by JZ
 --------------------------------------*/

/*
 * Load parameters to Param object
 * file_name : xml file name
 */
void load_params(const string &file_name);

/*
 * Save parameters from Param object to XML file
 * file_name : xml file name
 */
void save_params(const string &file_name);
#endif /* defined(__Xcode_Pixel_Proj__xmlHelper__) */
