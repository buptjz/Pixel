#include "qt_pixel_main.h"
#include "qtThread.h"
#include "imageConvert.h"
#include "superImagePatch.h"
#include "tools.h"
#include "params.h"
#include "logDisplay.h"
#include "tools.h"
#include "xmlHelper.h"
extern LogDisplay* logDisplay;
const int ICONSIZE_W = 60;
const int ICONSIZE_H = 60;
Ui::MainWindow qt_Pixel_Main::ui;
LogDisplay* logDisplay = new LogDisplay();

qt_Pixel_Main::qt_Pixel_Main(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.tabWidget->setStyleSheet("{background-color: rgba(215,215,215,0) }");
	
	this->image = new QImage();
	this->originalImage = new QImage();
	//this->superImagePatch = new QImage();
	//this->ImagePatch = new QImage();
	//����superImagePatch�б���ʽ
	ui.SuperImagePatchView->setIconSize(QSize(ICONSIZE_W, ICONSIZE_H));
	ui.SuperImagePatchView->setResizeMode(QListView::Adjust);
	ui.SuperImagePatchView->setViewMode(QListView::IconMode);
	ui.SuperImagePatchView->setMovement(QListView::Static);
	ui.SuperImagePatchView->setSpacing(10);
	ui.SuperImagePatchView->setWrapping(false);
	ui.SuperImagePatchView->setFlow(QListView::LeftToRight);

	//����ImagePatch�б���ʽ
	ui.ImagePatchView->setIconSize(QSize(ICONSIZE_W, ICONSIZE_H));
	ui.ImagePatchView->setResizeMode(QListView::Adjust);
	ui.ImagePatchView->setViewMode(QListView::IconMode);
	ui.ImagePatchView->setMovement(QListView::Static);
	ui.ImagePatchView->setSpacing(10);

	//log style
	ui.LogDisplay->setContentsMargins(1, 1, 1, 1);
	ui.LogDisplay->setReadOnly(true);
	ui.LogDisplay->setAlignment(Qt::AlignTop);

	//MatchType style (QComboBox)
	//ui.MatchType
	string matchType1 = Params::SURF;
	string matchType2 = Params::SHAPE_CONTEXT;
	string matchType3 = Params::SIFT;
	ui.MatchType->addItem(QWidget::tr(matchType1.c_str()));
	ui.MatchType->addItem(QWidget::tr(matchType2.c_str()));
	ui.MatchType->addItem(QWidget::tr(matchType3.c_str()));

	//SegmentType style (QComboBox)
	//ui.SegmentType
	string segmentType1 = Params::MORPH_BASIC;
	string segmentType2 = Params::EGBIS;
	ui.SegmentType->addItem(QWidget::tr(segmentType1.c_str()));
	ui.SegmentType->addItem(QWidget::tr(segmentType2.c_str()));


	//ui.RemoveDuplicateType
	ui.RemoveDuplicateType->addItem(QWidget::tr(matchType1.c_str()));
	ui.RemoveDuplicateType->addItem(QWidget::tr(matchType2.c_str()));
	ui.RemoveDuplicateType->addItem(QWidget::tr(matchType3.c_str()));


	//MatchType All style (QComboBox)
	//ui.MatchTypeAll
	ui.MatchTypeAll->addItem(QWidget::tr(matchType1.c_str()));
	ui.MatchTypeAll->addItem(QWidget::tr(matchType2.c_str()));
	ui.MatchTypeAll->addItem(QWidget::tr(matchType3.c_str()));

	//SegmentType style  All(QComboBox)
	//ui.SegmentTypeAll
	ui.SegmentTypeAll->addItem(QWidget::tr(segmentType1.c_str()));
	ui.SegmentTypeAll->addItem(QWidget::tr(segmentType2.c_str()));

	//����ImagePatchViewInOneImage�б���ʽ
	ui.ImagePatchViewInOneImage->setIconSize(QSize(ICONSIZE_W, ICONSIZE_H));
	ui.ImagePatchViewInOneImage->setResizeMode(QListView::Adjust);
	ui.ImagePatchViewInOneImage->setViewMode(QListView::IconMode);
	ui.ImagePatchViewInOneImage->setMovement(QListView::Static);
	ui.ImagePatchViewInOneImage->setSpacing(10);
	//����connect ��
	//receive log messge
	connect(logDisplay, SIGNAL(sig(QString)), this, SLOT(on_logDisplay(QString)) );
	connect(ui.OpenOriginalImageBtn, SIGNAL(clicked()), this, SLOT(on_openOriginalImageBtn_clicked()));
	connect(ui.OpenImageLibBtn, SIGNAL(clicked()), this, SLOT(on_ImageLibBtn_clicked()));
	connect(ui.RemoveDuplicateBtn, SIGNAL(clicked()), this, SLOT(on_removeDuplicateBtn_clicked()));
	connect(ui.SavePatches2DataBaseBtn, SIGNAL(clicked()), this, SLOT(on_SavePatches2DataBaseBtn_clicked()));

	connect(ui.OpensampleImageBtn, SIGNAL(clicked()), this, SLOT(on_openSampleImageBtn_clicked()));
	connect(ui.SearchBtn, SIGNAL(clicked()), this, SLOT(on_searchBtn_clicked()));
	connect(ui.SuperImagePatchView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_superImagePatch_Itemclicked(QListWidgetItem *)));
	connect(ui.ImagePatchView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_ImagePatch_Itemclicked(QListWidgetItem *)));

	connect(ui.AddinLibBtn, SIGNAL(clicked()), this, SLOT(on_Add2ImageLib_clicked()));

	connect(ui.SegmentBtn, SIGNAL(clicked()), this, SLOT(on_segmentBtn_clicked()) );

	connect(ui.SetMatchParasAllBtn, SIGNAL(clicked()), this, SLOT(setMatchParasAll()));
	connect(ui.SetSegmentParasAllBtn, SIGNAL(clicked()), this, SLOT(setSegmentParasAll()));
	connect(ui.SetMatchParasSearchBtn, SIGNAL(clicked()), this, SLOT(setMatchParasSearch()));

	connect(ui.SetSegmentParasInOneImageBtn, SIGNAL(clicked()), this, SLOT(setSegmentParasInOneImage()));
	connect(ui.SetMatchParasInOneImageBtn, SIGNAL(clicked()), this, SLOT(setMatchParasInOneImage()));

	connect(ui.ImagePatchViewInOneImage, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(on_imagePatchViewInOneImage_Itemclicked(QListWidgetItem *)));

	connect(ui.ShowAllSuperImagePatchesBtn, SIGNAL(clicked()), this, SLOT(showAllSuperImagePatches()));
	connect(ui.PreviousPageBtn, SIGNAL(clicked()), this, SLOT(previousPage()));
	connect(ui.NextPageBtn, SIGNAL(clicked()), this, SLOT(nextPage()));
	
}

qt_Pixel_Main::~qt_Pixel_Main()
{
	if (imageLibThread != NULL)
	{
		delete imageLibThread;
		imageLibThread = NULL;
	}
	if (searchBtnThread != NULL)
	{
		delete searchBtnThread;
		searchBtnThread = NULL;
	}
	if (superImagePatchItemclickedThread != NULL)
	{
		delete superImagePatchItemclickedThread;
		superImagePatchItemclickedThread = NULL;
	}
	if (imageLibThread != NULL)
	{
		delete image;
		image = NULL;
	}
	//delete superImagePatch;
	//delete ImagePatch;
}

//��ӡ��־��Ϣ
void qt_Pixel_Main::on_logDisplay(QString logQstr)
{
	qt_Pixel_Main::ui.LogDisplay->append(logQstr);
	//qt_Pixel_Main::ui.LogDisplay->setText(logQstr);
	qt_Pixel_Main::ui.LogDisplay->moveCursor(QTextCursor::End);
}



/*��ͼ���*/
void qt_Pixel_Main::on_ImageLibBtn_clicked()
{
	//ѡ��ͼ����ļ���·������ʾ·��
	dirPath = QFileDialog::getExistingDirectory(this, "Select a folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
	if (!dirPath.isEmpty())
	{
		ui.ImageLibPath->setText(dirPath);
	}
}

void qt_Pixel_Main::on_Add2ImageLib_clicked()
{
	//ui.LogDisplay->setText("many images are training!");
	imageLibThread = new ImageLibThread(dirPath);
	imageLibThread->start();
}

/*�򿪴��ָ�ͼ��*/
void qt_Pixel_Main::on_openOriginalImageBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
		this, "open image file",
		".",
		"Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
	if (fileName != "")
	{
		QString logQstr = QString("Load image ").append(fileName);
		logDisplay->logDisplay(logQstr.toStdString());
		if (originalImage->load(fileName))
		{
			//��������
			QGraphicsScene *scene = new QGraphicsScene;
			//����ͼƬ
			QSize size = ui.OriginalImageView->maximumViewportSize();
			QImage scaledImg = originalImage->scaled(size, Qt::KeepAspectRatio);

			//get the OriginalImageSegemented 
			string path = fileName.toStdString();//the direction of originalImages
			//construct OriginalImageId and newPath
			string pattern = "/";
			vector<std::string>  splitstr = split(path, pattern);
			string imageName = splitstr[splitstr.size() - 1];
			string newPath = "./" + Params::defaultPath + "/" + imageName;
			string originalImageId = Params::defaultPath + "_" + imageName;

			Mat *originalImagePatch = new  Mat(imread_and_preprocess(path));
			if (originalImageSegemented != NULL)
			{
				delete originalImageSegemented;
			}
			originalImageSegemented = NULL;
			originalImageSegemented = new OriginalImage(originalImageId, newPath, originalImagePatch);
		

			//������ʾͼƬ
			scene->addPixmap(QPixmap::fromImage(scaledImg));
			ui.OriginalImageView->setScene(scene);
			ui.OriginalImageView->show();
		}
		else
		{
			QMessageBox::information(NULL, tr("Error"), tr("File format error!"));
		}
	}
	else
	{
		QMessageBox::information(NULL, tr("Error"), tr("select a file!"));
	}
}

/*�ָ��ͼ��*/
void qt_Pixel_Main::on_segmentBtn_clicked()
{
	Params::segment_type_for_one_image = (ui.SegmentType->currentText()).toStdString();
	buttonClicked = SEGMENT;
	if (originalImageSegemented == NULL)
	{
		logDisplay->logDisplay("The image waiting for segmenting is not exist!");
		return;
	}
	if (segementedImagePatches.size() != 0)
	{
		for (int i = 0; i < segementedImagePatches.size(); i++)
		{
			delete segementedImagePatches[i];
		}
	}
	segementedImagePatches.clear();

	segmentBtnThread = new SegmentBtnThread(originalImageSegemented, &segementedImagePatches);
	//here main thread wait for segmentBtnThread excute 
	connect(segmentBtnThread, SIGNAL(sig()), this, SLOT(setSegmentedImagePatch()));
	segmentBtnThread->start();
}

//set segment ImagePatch	
void qt_Pixel_Main::setSegmentedImagePatch()
{
	if (ui.ImagePatchViewInOneImage->count() != 0)
	{
		ui.ImagePatchViewInOneImage->clear();
	}
	for (int i = 0; i < segementedImagePatches.size(); i++)
	{
		Patch* sip = segementedImagePatches[i];
		QImage showImage = Mat2QImage(*(sip->getOriginalImagePatch()));
		//convert int to string, for mark QIcon
		stringstream ss;
		string str;
		ss << (i + 1);
		ss >> str;
		//change QImage to QIcon and show 
		QPixmap qp = QPixmap::fromImage(showImage);
		ui.ImagePatchViewInOneImage->addItem(new QListWidgetItem(QIcon(qp), tr(str.c_str())));
	}
	logDisplay->logDisplay("Display image patches belong to the image " + originalImageSegemented->getPath() );
}

/*
�Ե���ͼ���е�ͼԪȥ��
*/
void qt_Pixel_Main::on_removeDuplicateBtn_clicked()
{
	if (segementedImagePatches.empty() || segementedImagePatches.size() == 0)
	{
		logDisplay->logDisplay("There is no segemented image patches to remove duplicate! ");
		return;
	}
	Params::featureType_for_one_image = (ui.RemoveDuplicateType->currentText()).toStdString();
	buttonClicked = REMOVEDUPLICATE;
	removeDuplicateBtnThread = new RemoveDuplicateBtnThread(&segementedImagePatches, &segementedSupeImagePatches);
	//here main thread wait for segmentBtnThread excute 
	connect(removeDuplicateBtnThread, SIGNAL(sig()), this, SLOT(setRemoveDuplicateSuperImagePatch()));
	removeDuplicateBtnThread->start();
}

//remove duplicate image patches segmented for one image, then set acquired super Image Patches in ui.ImagePatchViewInOneImage 
void qt_Pixel_Main::setRemoveDuplicateSuperImagePatch()
{
	if (ui.ImagePatchViewInOneImage->count() != 0)
	{
		ui.ImagePatchViewInOneImage->clear();
	}

	for (int i = 0; i < segementedSupeImagePatches.size(); i++)
	{
		Patch* sip = segementedSupeImagePatches[i];
		QImage showImage = Mat2QImage(*(sip->getOriginalImagePatch()));
		//change QImage to QIcon and show 
		QPixmap qp = QPixmap::fromImage(showImage);
		stringstream ss;
		string str;
		ss << (i + 1);
		ss >> str;
		ui.ImagePatchViewInOneImage->addItem(new QListWidgetItem(QIcon(qp), tr(str.c_str())));
	}
	logDisplay->logDisplay("Display super image patches of the input image.");
}

/*�洢����ͼ����ͼԪ����ͼԪ�����ݿ�*/
void qt_Pixel_Main::on_SavePatches2DataBaseBtn_clicked()
{
	logDisplay->logDisplay("Saving the image and its patches into database .... ....");
	savePatches2DataBaseBtnThread = new SavePatches2DataBaseBtnThread(originalImageSegemented, &segementedImagePatches, &segementedSupeImagePatches);
	savePatches2DataBaseBtnThread->start();
}
/*������ͼ��*/
void qt_Pixel_Main::on_openSampleImageBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
		this, "open image file",
		".",
		"Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
	if (fileName != "")
	{
		QString logQstr = QString("Load sample image ").append(fileName);
		logDisplay->logDisplay(logQstr.toStdString());
		if (image->load(fileName))
		{
			//��������
			QGraphicsScene *scene = new QGraphicsScene;
			//����ͼƬ
			QSize size = ui.SampleImageView->maximumViewportSize();
			QImage scaledImg = image->scaled(size, Qt::KeepAspectRatio);

			//get the sampleImage and change it to patch, process later in searchBtn operation
			string path = fileName.toStdString();
			Mat *originalImagePatch = new  Mat(imread_and_preprocess(path));

			Mat *binaryImagePatch = new Mat(originalImagePatch->rows, originalImagePatch->cols, Params::grey_image_type);
			cvtColor(*originalImagePatch, *binaryImagePatch, CV_BGR2GRAY, Params::grey_image_channels);
			if (patchCompared != NULL)
			{
				delete patchCompared;
			}
			patchCompared = new SuperImagePatch("patchCompared", binaryImagePatch, originalImagePatch);
			//������ʾͼƬ
			scene->addPixmap(QPixmap::fromImage(scaledImg));
			ui.SampleImageView->setScene(scene);
			ui.SampleImageView->show();
		}
		else
		{
			QMessageBox::information(NULL, tr("Error"), tr("File format error!"));
		}
	}
	else
	{
		QMessageBox::information(NULL, tr("Error"), tr("select a file!"));
	}
}

/*����*/
void qt_Pixel_Main::on_searchBtn_clicked()
{
	Params::featureType_for_search = (ui.MatchType->currentText()).toStdString();
	if (similarPatches.size() != 0)
	{
		for (int i = 0; i < similarPatches.size(); i++)
		{
			delete similarPatches[i].second;
		}
	}
	similarPatches.clear();
	searchBtnThread = new SearchBtnThread(&similarPatches, patchCompared);
	logDisplay->logDisplay("Searching similar super image patches in database ... ...");
	//here main thread wait for searchBtnThread excute 
	connect(searchBtnThread, SIGNAL(sig()), this, SLOT(setsuperImagePatch()));
	searchBtnThread->start();

}

//setsuperImagePatch
void qt_Pixel_Main::setsuperImagePatch()
{
	if (ui.SuperImagePatchView->count() != 0)
	{
		ui.SuperImagePatchView->clear();
	}

	for (int i = 0; i < similarPatches.size(); i++)
	{
		Patch* sip = similarPatches[i].second;
		QImage showImage = Mat2QImage(*(sip->getOriginalImagePatch()));
		//convert int to string, for mark QIcon
		double similarity = similarPatches[i].first;
		string str;
		str = to_string(i + 1) + ": " + to_string(similarity).substr(0, 4);
		//change QImage to QIcon and show 
		QPixmap qp = QPixmap::fromImage(showImage);
		ui.SuperImagePatchView->addItem(new QListWidgetItem(QIcon(qp), tr(str.c_str())));
	}
	logDisplay->logDisplay("Search similar super image patches in database finished");
}
/*�����ͼԪ���鿴��Ӧ��ͼԪ*/
void qt_Pixel_Main::on_superImagePatch_Itemclicked(QListWidgetItem *item)
{
	if (!item)
	{
		return;
	}
	if (ui.ImagePatchView->count() != 0)
	{
		ui.ImagePatchView->clear();
	}
	int itemnum = ui.SuperImagePatchView->row(item);
	if (imagePatchList.size() != 0)
	{
		for (int i = 0; i < imagePatchList.size(); i++)
		{
			delete imagePatchList[i];
		}		
	}
	imagePatchList.clear();
	logDisplay->logDisplay("Searching image patches belong to the super image patch clicked in database ... ...");
	SuperImagePatch *superImagePatch = (SuperImagePatch *)similarPatches[itemnum].second;

	superImagePatchItemclickedThread = new SuperImagePatchItemclickedThread(superImagePatch, &imagePatchList);
	//here main thread wait for searchBtnThread excute 
	connect(superImagePatchItemclickedThread, SIGNAL(sig()), this, SLOT(setImagePatch()));
	superImagePatchItemclickedThread->start();

}

//setImagePatch	
void qt_Pixel_Main::setImagePatch()
{
	if (ui.ImagePatchView->count() != 0)
	{
		ui.ImagePatchView->clear();
	}
	for (int i = 0; i < imagePatchList.size(); i++)
	{
		Patch* ip = imagePatchList[i];
		QImage showImage = Mat2QImage(*(ip->getOriginalImagePatch()));
		//convert int to string, for mark QIcon
		stringstream ss;
		string str;
		ss << (i + 1);
		ss >> str;
		//change QImage to QIcon and show 
		QPixmap qp = QPixmap::fromImage(showImage);
		ui.ImagePatchView->addItem(new QListWidgetItem(QIcon(qp), tr(str.c_str())));
	}
	logDisplay->logDisplay("Display image patches belong to the super image patch clicked.");
}

/*�����ͼԪ�鿴ԭͼ*/
void qt_Pixel_Main::on_ImagePatch_Itemclicked(QListWidgetItem *item)
{
	int itemIndex = ui.ImagePatchView->row(item);
	ImagePatch* iptemp = imagePatchList[itemIndex];
	Rect position = iptemp->getPosition();
	string originalImageId = iptemp->getOriginalImage()->getOriginalImageId();
	String originalImagePath = readOriginalImage(originalImageId)->getPath();
	logDisplay->logDisplay("Show image patch in original image.");
	imagePatchItemclickedThread = new ImagePatchItemclickedThread(position, originalImagePath);
	imagePatchItemclickedThread->start();
}

void qt_Pixel_Main::setMatchParasAll()
{
	Params::featureType_for_batch_image = (ui.MatchTypeAll->currentText()).toStdString();
	logDisplay->logDisplay("Setting match parameters of all images!");
	dialogMatchParasAll.getMatchParas();
	dialogMatchParasAll.show();
}

void qt_Pixel_Main::setSegmentParasAll()
{
	Params::segment_type_for_batch_image = (ui.SegmentTypeAll->currentText()).toStdString();
	logDisplay->logDisplay("Setting segment parameters of all images!");
	dialogSegmentParasAll.getSegmentParas();
	dialogSegmentParasAll.show();
}

void qt_Pixel_Main::setMatchParasSearch()
{
	Params::featureType_for_search = (ui.MatchType->currentText()).toStdString();
	logDisplay->logDisplay("Setting compare parameters while searching!");
	dialogMatchParasAll.getMatchParas();
	dialogMatchParasAll.show();
}

void qt_Pixel_Main::setSegmentParasInOneImage()
{
	Params::segment_type_for_one_image = (ui.SegmentType->currentText()).toStdString();
	logDisplay->logDisplay("Setting segment parameters of one image!");
	dialogSegmentParasAll.getSegmentParas();
	dialogSegmentParasAll.show();
}

void qt_Pixel_Main::setMatchParasInOneImage()
{
	Params::featureType_for_one_image = (ui.RemoveDuplicateType->currentText()).toStdString();
	logDisplay->logDisplay("Setting compare parameters of one image!");
	dialogMatchParasAll.getMatchParas();
	dialogMatchParasAll.show();
}

void qt_Pixel_Main::on_imagePatchViewInOneImage_Itemclicked(QListWidgetItem * item)
{
	if (!item)
	{
		return;
	}
	int itemnum = ui.ImagePatchViewInOneImage->row(item);
	logDisplay->logDisplay("Transmit the patch double clicked to search interace as an sample image.");
	//get the sampleImage and change it to patch, process later in searchBtn operation
	if (patchCompared != NULL)
	{
		delete patchCompared;
	}
	
	switch (buttonClicked)
	{
	case ButtonClicked::SEGMENT:
		patchCompared = segementedImagePatches[itemnum];
		break;
	case ButtonClicked::REMOVEDUPLICATE:
		patchCompared = segementedSupeImagePatches[itemnum];
		break;
	default :
		break;
	}
	
	*image = Mat2QImage(*patchCompared->getOriginalImagePatch());
	//��������
	QGraphicsScene *scene = new QGraphicsScene;
	//����ͼƬ
	QSize size = ui.SampleImageView->maximumViewportSize();
	QImage scaledImg = image->scaled(size, Qt::KeepAspectRatio);

	
	//������ʾͼƬ
	scene->addPixmap(QPixmap::fromImage(scaledImg));
	ui.SampleImageView->setScene(scene);
	ui.SampleImageView->show();
	ui.tabWidget->setCurrentIndex(1);
}


//��ʾ���г�ͼԪ
void qt_Pixel_Main::showAllSuperImagePatches()
{
	logDisplay->logDisplay("Showing All super image patches.");
}

//��ʾ��ͼԪ�����л���ǰһҳ
void qt_Pixel_Main::previousPage()
{
	logDisplay->logDisplay("Switch to previous page.");
}

//�л�����һҳ
void qt_Pixel_Main::nextPage()
{
	logDisplay->logDisplay("Switch to next page.");
}

//�رմ���ʱ�����ò���д�������ļ�
void qt_Pixel_Main::closeEvent(QCloseEvent *event)
{
	save_params(Params::xmlFileName);
}