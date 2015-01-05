#ifndef QT_PIXEL_MAIN_H
#define QT_PIXEL_MAIN_H

#include <QtWidgets/QMainWindow>
#include "ui_qt_pixel_main.h"
#include <qlistwidget.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include "qtThread.h"
#include "imagePatch.h"

class qt_Pixel_Main : public QMainWindow
{
	Q_OBJECT

public:
	qt_Pixel_Main(QWidget *parent = 0);
	~qt_Pixel_Main();
	ImageLibThread *imageLibThread = NULL;
	SearchBtnThread *searchBtnThread = NULL;
	SuperImagePatchItemclickedThread * superImagePatchItemclickedThread = NULL;
	ImagePatchItemclickedThread* imagePatchItemclickedThread = NULL;
	RemoveDuplicateBtnThread*  removeDuplicateBtnThread = NULL;
	SavePatches2DataBaseBtnThread * savePatches2DataBaseBtnThread = NULL;
	SegmentBtnThread *segmentBtnThread = NULL;

	QString dirPath;//ImageLibBtn open the dir
	Patch* patchCompared = NULL;
	OriginalImage* originalImageSegemented = NULL;
	vector<ImagePatch*> segementedImagePatches;
	vector<SuperImagePatch*> segementedSupeImagePatches;

	vector<pair<double, Patch*> >  similarPatches;
	vector<ImagePatch*> imagePatchList;

public:
	static Ui::MainWindow ui;

private:
	QImage *image = NULL;
	QImage *originalImage = NULL;
	//QImage *superImagePatch;
	//QImage *imagePatch;

	//viewerDialog viewerDlg;

	public slots:
	//display log
	void on_logDisplay(QString logQstr);

	void on_openOriginalImageBtn_clicked(); //打开待分割图像
	void on_segmentBtn_clicked();//分割单幅图像
	void setSegmentedImagePatch();//显示分割的图元

	void on_removeDuplicateBtn_clicked();//单幅图像去重
	void setRemoveDuplicateSuperImagePatch();//显示去重图像

	void on_SavePatches2DataBaseBtn_clicked();//存储单幅图像及其图元、超图元入数据库

	void on_ImageLibBtn_clicked();  //点击图像库
	void on_Add2ImageLib_clicked();//add new images to library,  running in the background 

	void on_openSampleImageBtn_clicked(); //打开样本图
	void on_searchBtn_clicked();  //搜索

	void on_superImagePatch_Itemclicked(QListWidgetItem *item);  //点击超图元查看对应所有子图
	void on_ImagePatch_Itemclicked(QListWidgetItem *item);  //点击子图元查看原图

	void setsuperImagePatch();
	void setImagePatch();


};

#endif