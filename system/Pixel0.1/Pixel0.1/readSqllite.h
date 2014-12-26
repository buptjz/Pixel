#ifndef READSQLLITE_H
#define READSQLLITE_H
#include "originalImage.h"

OriginalImage* readOriginalImage( string originalImageId);
ImagePatch* readImagePatch(string imagePatchId);
SuperImagePatch* readSuperImagePatch(string superImagePatchId);
#endif