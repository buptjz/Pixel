#ifndef READSQLLITE_H
#define READSQLLITE_H
#include "originalImage.h"

OriginalImage* readOriginalImage(const string &originalImageId);
ImagePatch* readImagePatch(string imagePatchId);
SuperImagePatch* readSuperImagePatch(string superImagePatchId);
vector<Patch*> readAllSuperImagePatches();
int updateImagePatchTable(SuperImagePatch & sip);
#endif