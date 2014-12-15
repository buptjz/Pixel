#include<iostream>
#include"superImagePatch.h"
#include "imagePatch.h"
#include "originalImage.h"
#include<string>
#include<highgui.h>
#include<cv.h>

#include<io.h>
using namespace std;
using namespace cv;

list<SuperImagePatch*> removeDuplicateImagePatchs(list<ImagePatch*>&);
list<SuperImagePatch*> removeDuplicateSuperImagePatchs(list<SuperImagePatch*>&);
int main(int agrc, char **agrv){

	/*//������������
	//����cvLoadImage()�ĵ�1 ��������ͼ���ļ���·��. ��2 �������Ƕ�ȡͼ��ķ�ʽ:-1 ��ʾ����ͼ�������������ȡ,1 ��ʾǿ�Ʋ�ɫ��,0 ��ʾǿ�ƻ�ֵ��.
	IplImage* image = cvLoadImage("D:\\demo.jpg", -1);
	if (image == NULL)
	{
	cout << "�޷���ȡͼ������!" << endl;
	return -1;
	}
	//�ú����Ĺ����ǰ���ָ����ʽ����һ������,������ʾͼ�񡣵�1 �������Ǵ��ڵ�����,�Լ������������ã���2 ��������ʾ���ڵĴ�С���Զ�����ͼ��ߴ���仯
	cvNamedWindow("ͼ����ʾ", CV_WINDOW_AUTOSIZE);
	//�ú����Ĺ�������ָ���Ĵ�������ʾͼ�񡣵�1 ����������ʾͼ�񴰿ڵ�����,��2 ��������Ҫ��ʾ��ͼ��
	cvShowImage("ͼ����ʾ", image);
	//�ú����Ĺ����ǽ�ͼ�����Ϊ����1 �������Ǳ����·��,�Լ�������������·��;��2 ��������Ҫ�����ͼ��
	cvSaveImage("D:\\saveImage.jpg", image);
	cvWaitKey(0);//һֱ�ȴ�����û�����Ļ�ͼ����������ʾ
	cvReleaseImage(&image);//�ͷ�ͼ���ڴ�
	cvDestroyWindow("ͼ����ʾ");//���ٴ�����Դ
	*/

	list<SuperImagePatch*> allSuperImagePatchs;
	string imageName;//����ͼ���ļ������� 
	string path;//ͼ���ļ�·��
	string fileName = "TestImage";//��ԭͼƬ���ļ�����
	string fileAddress = "D:/" + fileName;//�ļ���·��
	
	//�����ļ������ͼ���ļ�
	_finddata_t fileinfo;
	int handle = _findfirst((fileAddress + "/*").c_str(), &fileinfo);
	while (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
		_findnext(handle, &fileinfo);
	while (handle != -1)
	{
		//�����һ��ͼ����д���
		//=========================================================
		path = fileAddress + "/" + fileinfo.name;
		//����OriginalImage��Ķ���ori
		string originalImageId = fileName + "_" + imageName;
		OriginalImage *ori = new OriginalImage(path, originalImageId);
		IplImage *pImage = cvLoadImage(path.c_str(), -1);
		ori->setImage(pImage);

		//��ori�ָ��õ�СͼԪ�ļ���patchs��������������ݿ�
		list<ImagePatch*> patchs = ori->segmentImage();
		ori->saveOriginalImage();

		//patchs������СͼԪ����һ��ȥ�أ�����ȥ�غ��SuperImagePatch��Ķ��󼯺�
		list<SuperImagePatch*> sip = removeDuplicateImagePatchs(patchs);
		//=========================================================
		//�����о���һ��ȥ�صĳ�ͼԪ�洢�������ȴ�������һ��ȥ��
		list<SuperImagePatch*>::iterator  itor = sip.begin();
		while (itor != sip.end())
		{
			allSuperImagePatchs.push_back(*itor++);
		}
	
		if (_findnext(handle, &fileinfo) == -1) break;
	}
	_findclose(handle);


	//�Խ���һ��ȥ�غ�ĳ�ͼԪ�ٴ�ȥ�أ��������յ�SuperImagePatch��Ķ��󼯺�
	list<SuperImagePatch*> fsip = removeDuplicateSuperImagePatchs(allSuperImagePatchs);

	//����ͼԪ�������ݿⲢ������ͼԪ��
	list<SuperImagePatch*>::iterator  itor = fsip.begin();
	while (itor != fsip.end())
	{	
		//������Ҫ�ѳ�ͼԪ���������ݿ��в�������ͼԪ���е�superImagePatchId
		((SuperImagePatch*)*itor)->savePatch();
		//
		itor++;
	}

	return 0;
}

