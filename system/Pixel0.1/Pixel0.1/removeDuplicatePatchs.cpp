#include "imagePatch.h"
#include "superImagePatch.h"
/*
对一幅图像分割后得到的所有小图元进行一次去重，返回去重后的SuperImagePatch类的对象集合
输入：一幅图像分割后得到的所有小图元
输出：超图元
*/
list<SuperImagePatch*> removeDuplicateImagePatchs(list<ImagePatch*>&){
	list<SuperImagePatch*> result;
	return result;
}

/*
对进行一次去重后的超图元再次去重，返回最终的SuperImagePatch类的对象集合
输入：单幅图像去重后得到的超图元
输出：最终需要存储的超图元
*/
list<SuperImagePatch*> removeDuplicateSuperImagePatchs(list<SuperImagePatch*>&){
	list<SuperImagePatch*> result;
	return result;
}