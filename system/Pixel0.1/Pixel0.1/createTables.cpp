#include "sqlliteHelper.h"
SQLiteHelper sql_lite_helper;
bool creatTables()
{
	//创建数据库
	int dataBaseRes = sql_lite_helper.OpenDB("./Pixel.db3");
	//创建originalImage表
	int createOriginalImageRes = sql_lite_helper.CreateTable("originalImage (originalImageId varchar,  path varchar)");
	//创建imagePatch表
	int createImagePatchRes = sql_lite_helper.CreateTable("imagePatch(imagePatchId varchar, originalImageId varchar, superImagePatchId varchar, position )");
	//创建superImagePatch表
	int createSuperImagePatchRes = sql_lite_helper.CreateTable("");
	return true;
}