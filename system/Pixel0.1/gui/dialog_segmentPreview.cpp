#include "dialog_segmentPreview.h"
#include <originalImage.h>
#include <tools.h>
#include <params.h>
#include "imageConvert.h"
#include "logDisplay.h"
extern LogDisplay* logDisplay;

const int SLIDER_MIN = 1;
const int SLIDER_MAX = 200;
DialogSegmentPreview::DialogSegmentPreview(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//spinBox and slider initialization 
	ui.expectedPatchesNumSlider->setRange(SLIDER_MIN, SLIDER_MAX);
	ui.expectedPatchesNumspinBox->setRange(SLIDER_MIN, SLIDER_MAX);
	ui.expectedPatchesNumSlider->setValue(20);
	ui.expectedPatchesNumspinBox->setValue(20);

	//connect(ui.expectedPatchesNumSlider, SIGNAL(valueChanged(int)),this,SLOT(on_expectedPatchesNumSlider_valueChanged(int)));
	connect(ui.expectedPatchesNumSlider, SIGNAL(valueChanged(int)), ui.expectedPatchesNumspinBox, SLOT(setValue(int)));
	connect(ui.expectedPatchesNumspinBox, SIGNAL(valueChanged(int)), ui.expectedPatchesNumSlider, SLOT(setValue(int)));
	connect(ui.PreviewSegmentImageBtn, SIGNAL(clicked()), this, SLOT(on_previewSegmentImageBtn_clicked()));
	connect(ui.OKSegmentPreviewImageBtn, SIGNAL(clicked()), this, SLOT(on_oKSegmentPreviewImageBtn_clicked()));
	
}

DialogSegmentPreview::~DialogSegmentPreview()
{

}


void DialogSegmentPreview::setSegmentImage( OriginalImage* ori)
{
	this->segmentImage = ori;
}

//void DialogSegmentPreview::setSegmentImagePatchListInDialog(vector<ImagePatch*> *segementedImagePatches)
//{
//	this->segementedImagePatches = segementedImagePatches;
//}

void DialogSegmentPreview::on_previewSegmentImageBtn_clicked()
{
	expectedPatchesNum = ui.expectedPatchesNumspinBox->value();
	Params::segment_expect = expectedPatchesNum;
	string segmentType = Params::segment_type_for_one_image;
	segmentImageForPreview(segmentType);
}

void DialogSegmentPreview::segmentImageForPreview(string segment_type)
{	
	connect_num = segmentImage->get_connected_map(segment_type);
	Mat color_ret;
	connected_component2color_image(*(segmentImage->getRegImage()), connect_num, color_ret);

	QImage showImage = Mat2QImage(color_ret);
	QGraphicsScene *scene = new QGraphicsScene;
	//����ͼƬ
	QSize size = ui.regImageColorretView->maximumViewportSize();
	QImage scaledImg = showImage.scaled(size, Qt::KeepAspectRatio);
	//������ʾͼƬ
	scene->addPixmap(QPixmap::fromImage(scaledImg));
	ui.regImageColorretView->setScene(scene);
	ui.regImageColorretView->show();
}
/*void DialogSegmentPreview::on_configSegImageBtn_clicked()
{
	segmentImage.connect_num = connect_num;
	
}*/
void DialogSegmentPreview::on_oKSegmentPreviewImageBtn_clicked(){
	//*(this->segementedImagePatches) = segmentImage.get_patches(connect_num);
	emit this->sig(connect_num);
	logDisplay->logDisplay("Emit a signal for mainWindow.");
	this->close();
	
}