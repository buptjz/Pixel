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
	QString dirPath;//ImageLibBtn open the dir
	Patch* patchCompared = NULL;

	vector<pair<double, Patch*> >  similarPatches;
	vector<ImagePatch*> imagePatchList;

public:
	static Ui::MainWindow ui;

private:
	QImage *image = NULL;
	//QImage *superImagePatch;
	//QImage *imagePatch;

	//viewerDialog viewerDlg;

	public slots:
	void on_ImageLibBtn_clicked();  //���ͼ���
	void on_Add2ImageLib_clicked();//add new images to library,  running in the background 

	void on_openSampleImageBtn_clicked(); //������ͼ
	void on_searchBtn_clicked();  //����

	void on_superImagePatch_Itemclicked(QListWidgetItem *item);  //�����ͼԪ�鿴��Ӧ������ͼ
	void on_ImagePatch_Itemclicked(QListWidgetItem *item);  //�����ͼԪ�鿴ԭͼ

	void setsuperImagePatch();
	void setImagePatch();


};

#endif