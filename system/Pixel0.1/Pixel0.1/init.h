#ifndef INIT_H
#define INIT_H
#include "qt_pixel_main.h"
#include <QtWidgets/QApplication>
#include "sqlliteHelper.h"
#include<string>
#include<cv.h>
#include<io.h>
#include "readSqllite.h"
#include "tools.h"
#include "params.h"
#include<fstream>
#include <direct.h>
#include "logDisplay.h"
extern LogDisplay* logDisplay;
/*
1. check database whether exists  and open database
2. check the file in which users save an external image whether exist
3. read params form xml when run the project
4. exec push_attr() in params.cpp to built an dictionary of params
*/
 void init();
#endif