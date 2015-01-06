#include "dialog_segmentParasAll.h"
#include "params.h"

DialogSegmentParasAll::DialogSegmentParasAll(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.OKbtn_segmentParasAll, SIGNAL(clicked()), this, SLOT(on_OKbtn_segmentParasAll()));
	connect(ui.CancelBtn_segmentParasAll, SIGNAL(clicked()), this, SLOT(close()));
}

DialogSegmentParasAll::~DialogSegmentParasAll()
{
}
void DialogSegmentParasAll::setSegmentParas()
{
	//set patches segment parameters 
	Params::retry_max = atoi((ui.lineEdit_retry_max->text()).toStdString().c_str());
	

}

void DialogSegmentParasAll::getSegmentParas()
{
	ui.lineEdit_retry_max->setText(QString::fromStdString(to_string(Params::retry_max)));
	ui.lineEdit_segment_expect_upboard->setText(QString::fromStdString(to_string(Params::segment_expect_upboard)));
	ui.lineEdit_segment_expect_lowboard->setText(QString::fromStdString(to_string(Params::segment_expect_lowboard)));
	ui.lineEdit_segment_expect->setText(QString::fromStdString(to_string(Params::segment_expect)));
	ui.lineEdit_patch_pixel_min->setText(QString::fromStdString(to_string(Params::patch_pixel_min)));
	ui.lineEdit_patch_pixel_max->setText(QString::fromStdString(to_string(Params::patch_pixel_max)));
	ui.lineEdit_segment_step->setText(QString::fromStdString(to_string(Params::segment_step)));

	ui.lineEdit_morph_min->setText(QString::fromStdString(to_string(Params::morph_min)));

	ui.lineEdit_egbis_sigma->setText(QString::fromStdString(to_string(Params::egbis_sigma)));
	ui.lineEdit_egbis_c->setText(QString::fromStdString(to_string(Params::egbis_c)));
	ui.lineEdit_egbis_min_size->setText(QString::fromStdString(to_string(Params::egbis_min_size)));
}


void DialogSegmentParasAll::on_OKbtn_segmentParasAll()
{
	setSegmentParas();
	this->close();
}