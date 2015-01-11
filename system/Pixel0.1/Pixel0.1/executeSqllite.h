#ifndef EXECUTESQLLITE_H
#define EXECUTESQLLITE_H
#include <string>
#include "superImagePatch.h"
using namespace std;
void deleteAnSuperImagePatch(string superImagePatchId);
void deleteAnImagePatch(string imagePatchId);
void deleteAnSuperImagePatchAndItsImagePatches(SuperImagePatch * superImagePatch);
void addCategoryOfSuperImagePatch(string category, SuperImagePatch *superImagePatch);
#endif