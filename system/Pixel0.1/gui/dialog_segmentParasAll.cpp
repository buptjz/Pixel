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
	//Params::retry_max = atoi((ui.lineEdit_retry_max->text()).toStdString().c_str());
	string retry_max = (ui.lineEdit_retry_max->text()).toStdString();
	string segment_expect_upboard = (ui.lineEdit_segment_expect_upboard->text()).toStdString();
	string segment_expect_lowboard = (ui.lineEdit_segment_expect_lowboard->text()).toStdString();
	string segment_expect = (ui.lineEdit_segment_expect->text()).toStdString();
	string patch_pixel_min = (ui.lineEdit_patch_pixel_min->text()).toStdString();
	string patch_pixel_max = (ui.lineEdit_patch_pixel_max->text()).toStdString();
	string segment_step = (ui.lineEdit_segment_step->text()).toStdString();
	string pixel_rat_min = (ui.lineEdit_pixel_rat_min->text()).toStdString();
	Params::set_attr("retry_max", retry_max.c_str());
	Params::set_attr("segment_expect_upboard", segment_expect_upboard.c_str());
	Params::set_attr("segment_expect_lowboard", segment_expect_lowboard.c_str());
	Params::set_attr("segment_expect", segment_expect.c_str());
	Params::set_attr("patch_pixel_min", patch_pixel_min.c_str());
	Params::set_attr("patch_pixel_max", patch_pixel_max.c_str());
	Params::set_attr("segment_step", segment_step.c_str());
	Params::set_attr("pixel_rat_min", pixel_rat_min.c_str());

	string morph_min = (ui.lineEdit_morph_min->text()).toStdString();
	Params::set_attr("morph_min", morph_min.c_str());

	string egbis_sigma = (ui.lineEdit_egbis_sigma->text()).toStdString();
	string egbis_c = (ui.lineEdit_egbis_c->text()).toStdString();
	string egbis_min_size = (ui.lineEdit_egbis_min_size->text()).toStdString();
	Params::set_attr("egbis_sigma", egbis_sigma.c_str());
	Params::set_attr("egbis_c", egbis_c.c_str());
	Params::set_attr("egbis_min_size", egbis_min_size.c_str());

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

	ui.lineEdit_pixel_rat_min->setText(QString::fromStdString(to_string(Params::pixel_rat_min)));
}


void DialogSegmentParasAll::on_OKbtn_segmentParasAll()
{
	setSegmentParas();
	this->close();
}