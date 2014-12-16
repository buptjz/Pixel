#include "sqlliteHelper.h"
SQLiteHelper sql_lite_helper;
bool creatTables()
{
	//创建数据库
	int res = sql_lite_helper.OpenDB("./Pixel.db3");
	//创建originalImage表
	int createRes = sql_lite_helper.CreateTable("originalImage (originalImageId varchar,  path varchar)");
	//

	return true;
}