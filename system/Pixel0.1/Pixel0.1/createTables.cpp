#include "sqlliteHelper.h"
SQLiteHelper sql_lite_helper;
bool creatTables()
{
	//�������ݿ�
	int dataBaseRes = sql_lite_helper.OpenDB("./Pixel.db3");
	//����originalImage��
	int createOriginalImageRes = sql_lite_helper.CreateTable("originalImage (originalImageId varchar,  path varchar)");
	//����imagePatch��
	int createImagePatchRes = sql_lite_helper.CreateTable("imagePatch(imagePatchId varchar, originalImageId varchar, superImagePatchId varchar, position )");
	//����superImagePatch��
	int createSuperImagePatchRes = sql_lite_helper.CreateTable("");
	return true;
}