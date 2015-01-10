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
	int currentPage = 0;//��ʾ��ͼԪ���棬��ǰ����ҳ��
	int quantityOfSuperImagePatchesInDatabase = 0;//���ݿ��г�ͼԪ����
	int pageMax = 0; //���ҳ��

	QString dirPath;//ImageLibBtn open the dir
	Patch* patchCompared = NULL;//"����"����򿪵�ͼ��

	OriginalImage* originalImageSegemented = NULL;//���ָ��������ͼ��
	vector<ImagePatch*> segementedImagePatches;
	vector<SuperImagePatch*> segementedSupeImagePatches;
	enum ButtonClicked buttonClicked = NOTCLICKED;//"�ָ�"�����ж����������"�ָ�"����"ȥ��"��ť

	vector<pair<double, Patch*> >  similarPatches;//"����"����õ������Ƴ�ͼԪ
	vector<ImagePatch*> imagePatchList;//�ɳ�ͼԪ�ҵ���ͼԪ

	vector<Patch*>  superImagePatchesInPageReadFromDatabase; //��ҳ��ʾ���г�ͼԪ��һ�μ��صĳ�ͼԪ
public:
	static Ui::MainWindow ui;
	DialogMatchParasAll  dialogMatchParasAll;
	DialogSegmentParasAll dialogSegmentParasAll;


public:
	// ʵ��QWidget�е��麯��closeEvent(QCloseEvent*);  
	void closeEvent(QCloseEvent *event);

private:
	QImage *image = NULL;
	QImage *originalImage = NULL;


public slots:
	//display log
	void on_logDisplay(QString logQstr);

	void on_openOriginalImageBtn_clicked(); //�򿪴��ָ�ͼ��
	void on_segmentBtn_clicked();//�ָ��ͼ��
	void setSegmentedImagePatch();//��ʾ�ָ��ͼԪ

	void on_removeDuplicateBtn_clicked();//����ͼ��ȥ��
	void setRemoveDuplicateSuperImagePatch();//��ʾȥ��ͼ��

	void on_SavePatches2DataBaseBtn_clicked();//�洢����ͼ����ͼԪ����ͼԪ�����ݿ�

	void on_ImageLibBtn_clicked();  //���ͼ���
	void on_Add2ImageLib_clicked();//add new images to library,  running in the background 

	void on_openSampleImageBtn_clicked(); //������ͼ
	void on_searchBtn_clicked();  //����

	void on_superImagePatch_Itemclicked(QListWidgetItem *item);  //�����ͼԪ�鿴��Ӧ������ͼ
	void on_ImagePatch_Itemclicked(QListWidgetItem *item);  //�����ͼԪ�鿴ԭͼ

	void setsuperImagePatch();
	void setImagePatch();


	void setMatchParasAll();//���á�������⡱�����ƥ�����
	void setSegmentParasAll();//���á�������⡱����ķָ����

	void setMatchParasSearch();//���á�����������ƥ�����

	void setSegmentParasInOneImage();//���á��ָ����ķָ����
	void setMatchParasInOneImage();//���á��ָ����ȥ�ز���


	void on_imagePatchViewInOneImage_Itemclicked(QListWidgetItem * item);//˫�����ָ����ͼԪչʾ�б��е�ͼԪ������ͼԪ������һ������������Ϊ����ͼ��

	void showAllSuperImagePatchesInPage();//��ҳ��ʾ���г�ͼԪ
	void previousPage();//��ʾ��ͼԪ�����л���ǰһҳ
	void nextPage();//�л�����һҳ
	void setsuperImagePatchInPage();
};

#endif