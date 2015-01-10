#ifndef QT_PIXEL_MAIN_H
#define QT_PIXEL_MAIN_H

#include "dialog_matchParasAll.h"
#include "dialog_segmentParasAll.h"
#include <QtWidgets/QMainWindow>
#include "ui_qt_pixel_main.h"
#include <qlistwidget.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include "qtThread.h"
#include "imagePatch.h"


enum ButtonClicked
{
	NOTCLICKED, SEGMENT, REMOVEDUPLICATE
};

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

	ShowAllSuperImagePatchesBtnThread* showAllSuperImagePatchesBtnThread = NULL;
	int currentPage = 0;//显示超图元界面，当前所在页数
	int quantityOfSuperImagePatchesInDatabase = 0;//数据库中超图元个数
	int pageMax = 0; //最大页数

	QString dirPath;//ImageLibBtn open the dir
	Patch* patchCompared = NULL;//"搜索"界面打开的图像

	OriginalImage* originalImageSegemented = NULL;//“分割”界面读入的图像
	vector<ImagePatch*> segementedImagePatches;
	vector<SuperImagePatch*> segementedSupeImagePatches;
	enum ButtonClicked buttonClicked = NOTCLICKED;//"分割"界面判断最后点击的是"分割"还是"去重"按钮

	vector<pair<double, Patch*> >  similarPatches;//"搜索"界面得到的相似超图元
	vector<ImagePatch*> imagePatchList;//由超图元找到的图元

	vector<Patch*>  superImagePatchesInPageReadFromDatabase; //分页显示所有超图元，一次加载的超图元
public:
	static Ui::MainWindow ui;
	DialogMatchParasAll  dialogMatchParasAll;
	DialogSegmentParasAll dialogSegmentParasAll;


public:
	// 实现QWidget中的虚函数closeEvent(QCloseEvent*);  
	void closeEvent(QCloseEvent *event);

private:
	QImage *image = NULL;
	QImage *originalImage = NULL;


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


	void setMatchParasAll();//设置“批量入库”界面的匹配参数
	void setSegmentParasAll();//设置“批量入库”界面的分割参数

	void setMatchParasSearch();//设置“检索”界面匹配参数

	void setSegmentParasInOneImage();//设置“分割”界面的分割参数
	void setMatchParasInOneImage();//设置“分割”界面去重参数


	void on_imagePatchViewInOneImage_Itemclicked(QListWidgetItem * item);//双击“分割”界面图元展示列表中的图元；将该图元传入下一个检索界面作为检索图像。

	void showAllSuperImagePatchesInPage();//分页显示所有超图元
	void previousPage();//显示超图元界面切换到前一页
	void nextPage();//切换到下一页
	void setsuperImagePatchInPage();
};

#endif