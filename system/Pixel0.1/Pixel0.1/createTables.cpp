#include "sqlliteHelper.h"
SQLiteHelper sql_lite_helper;
bool creatTables()
{
	//�������ݿ�
	int res = sql_lite_helper.OpenDB("./Pixel.db3");
	//����originalImage��
	int createRes = sql_lite_helper.CreateTable("originalImage (originalImageId varchar,  path varchar)");
	//

	return true;
}