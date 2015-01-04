#include "qt_pixel_main.h"
#include "qtThread.h"
#include "imageConvert.h"
#include "superImagePatch.h"
#include "tools.h"
#include "params.h"
#include "logDisplay.h"

const int ICONSIZE_W = 60;
const int ICONSIZE_H = 60;
Ui::MainWindow qt_Pixel_Main::ui;
LogDisplay* logDisplay = new LogDisplay();

qt_Pixel_Main::qt_Pixel_Main(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.tabWidget->setStyleSheet("{background-color: rgba(215,215,215,0) }");
	
	this->image = new QImage();
	//this->superImagePatch = new QImage();
	//this->ImagePatch = new QImage();
	//设置superImagePatch列表样式
	ui.SuperImagePatchView->setIconSize(QSize(ICONSIZE_W, ICONSIZE_H));
	ui.SuperImagePatchView->setResizeMode(QListView::Adjust);
	ui.SuperImagePatchView->setViewMode(QListView::IconMode);
	ui.SuperImagePatchView->setMovement(QListView::Static);
	ui.SuperImagePatchView->setSpacing(10);
	ui.SuperImagePatchView->setWrapping(false);
	ui.SuperImagePatchView->setFlow(QListView::LeftToRight);

	//设置ImagePatch列表样式
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
	//ui.Match
	string type1 = Params::SURF;
	string type2 = Params::SHAPE_CONTEXT;
	string type3 = Params::SIFT;
	ui.MatchType->addItem(QWidget::tr(type1.c_str()));
	ui.MatchType->addItem(QWidget::tr(type2.c_str()));
	ui.MatchType->addItem(QWidget::tr(type3.c_str()));

	//设置connect 槽
	//receive log messge
	connect(logDisplay, SIGNAL(sig(QString)), this, SLOT(on_logDisplay(QString)) );
	connect(ui.OpenImageLibBtn, SIGNAL(clicked()), this, SLOT(on_ImageLibBtn_clicked()));

	connect(ui.OpensampleImageBtn, SIGNAL(clicked()), this, SLOT(on_openSampleImageBtn_clicked()));
	connect(ui.SearchBtn, SIGNAL(clicked()), this, SLOT(on_searchBtn_clicked()));
	connect(ui.SuperImagePatchView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_superImagePatch_Itemclicked(QListWidgetItem *)));
	connect(ui.ImagePatchView, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_ImagePatch_Itemclicked(QListWidgetItem *)));

	connect(ui.AddinLibBtn, SIGNAL(clicked()), this, SLOT(on_Add2ImageLib_clicked()));
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

//打印日志信息
void qt_Pixel_Main::on_logDisplay(QString logQstr)
{
	qt_Pixel_Main::ui.LogDisplay->setText(logQstr);
	qt_Pixel_Main::ui.LogDisplay->moveCursor(QTextCursor::End);
}
/*打开图像库*/
void qt_Pixel_Main::on_ImageLibBtn_clicked()
{
	//选择图像库文件夹路径，显示路径
	dirPath = QFileDialog::getExistingDirectory(this, "Select a folder", QDir::currentPath(), QFileDialog::ShowDirsOnly);
	if (!dirPath.isEmpty())
	{
		ui.ImageLibPath->setText(dirPath);
	}
}

void qt_Pixel_Main::on_Add2ImageLib_clicked()
{
	//ui.LogDisplay->setText("many images are training!");
	logDisplay->logDisplay("images are training ... ... ");
	imageLibThread = new ImageLibThread(dirPath);
	imageLibThread->start();


}
/*打开样本图像*/
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
			//建立场景
			QGraphicsScene *scene = new QGraphicsScene;
			//缩放图片
			QSize size = ui.SampleImageView->maximumViewportSize();
			QImage scaledImg = image->scaled(size, Qt::KeepAspectRatio);

			//get the sampleImage and change it to patch, process later in searchBtn operation
			Mat oipTemp = QImage2Mat(*image);
			oipTemp.convertTo(oipTemp, Params::color_image_type);
			Mat *originalImagePatch = new Mat(oipTemp);
			Mat *binaryImagePatch = new Mat(originalImagePatch->rows, originalImagePatch->cols, Params::grey_image_type);

			patchCompared = new SuperImagePatch("patchCompared", originalImagePatch, binaryImagePatch);

			//加载显示图片
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

/*搜索*/
void qt_Pixel_Main::on_searchBtn_clicked()
{
	Params::featureType = (ui.MatchType->currentText()).toStdString();
	similarPatches.clear();
	searchBtnThread = new SearchBtnThread(&similarPatches, patchCompared);
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
		stringstream ss;
		string str;
		ss << (i + 1);
		ss >> str;
		//change QImage to QIcon and show 
		QPixmap qp = QPixmap::fromImage(showImage);
		ui.SuperImagePatchView->addItem(new QListWidgetItem(QIcon(qp), tr(str.c_str())));
	}
}
/*点击超图元，查看相应子图元*/
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
	imagePatchList.clear();
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
}

/*点击子图元查看原图*/
void qt_Pixel_Main::on_ImagePatch_Itemclicked(QListWidgetItem *item)
{
	int itemIndex = ui.ImagePatchView->row(item);
	ImagePatch* iptemp = imagePatchList[itemIndex];
	Rect position = iptemp->getPosition();
	string originalImageId = iptemp->getOriginalImage()->getOriginalImageId();
	String originalImagePath = readOriginalImage(originalImageId)->getPath();

	imagePatchItemclickedThread = new ImagePatchItemclickedThread(position, originalImagePath);
	imagePatchItemclickedThread->start();
}

