#include "executeSqllite.h"
#include "sqlliteHelper.h"
#include "logDisplay.h"
extern LogDisplay* logDisplay;
void deleteAnSuperImagePatch(string superImagePatchId)
{
	string str_sql = "delete from superImagePatch where superImagePatchId = '" + superImagePatchId + "'";
	int res = SQLiteHelper::Delete(str_sql.c_str());
	if (res == -1){
		logDisplay->logDisplay("Delete superImagePatch: " + superImagePatchId + "   failed!");
		return;
	}
	logDisplay->logDisplay("Delete superImagePatch: " + superImagePatchId + "   successed.");
}
void deleteAnImagePatch(string imagePatchId)
{
	string str_sql = "delete  from imagePatch where imagePatchId = '" + imagePatchId + "'";
	int res = SQLiteHelper::Delete(str_sql.c_str());
	if (res == -1){
		logDisplay->logDisplay("Delete imagePatch: " + imagePatchId + "  failed!");
		return;
	}
	logDisplay->logDisplay("Delete imagePatch : " + imagePatchId + "  successed.");
}
void deleteAnSuperImagePatchAndItsImagePatches(SuperImagePatch * superImagePatch)
{
	vector<string> patchIdList = superImagePatch->getPatchIdList();
	logDisplay->logDisplay("Delete superImagePatch whose id= " + superImagePatch->getSuperImagePatchId());
	deleteAnSuperImagePatch(superImagePatch->getSuperImagePatchId());
	for (int i = 0; i < patchIdList.size(); i++)
	{
		deleteAnImagePatch(patchIdList[i]);
	}
}
//----------------
void addCategoryOfSuperImagePatch(string category, SuperImagePatch *superImagePatch)
{
	logDisplay->logDisplay("Add category to a superImagePatch whose id= " + superImagePatch->getSuperImagePatchId());
	string superImagePatchId = superImagePatch->getSuperImagePatchId();
	string str_sql = "update superImagePatch set category = '" + category + "' where superImagePatchId = '" + superImagePatchId + "'";
	int res = SQLiteHelper::Update(str_sql.c_str());
	if (res == -1){
		logDisplay->logDisplay("Add CategoryOfSuperImagePatch: " + superImagePatchId + "   failed!");
		return;
	}
	logDisplay->logDisplay("Add CategoryOfSuperImagePatch: " + superImagePatchId + "   successed.");
}