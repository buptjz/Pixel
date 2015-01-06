#include "dialog_matchParasAll.h"
#include "params.h"
DialogMatchParasAll::DialogMatchParasAll(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.OKbtn_matchParasAll, SIGNAL(clicked()), this, SLOT(on_OKbtn_matchParasAll()));
	connect(ui.CancelBtn_matchParasAll, SIGNAL(clicked()), this, SLOT(close())); 
}

DialogMatchParasAll::~DialogMatchParasAll()
{
}
void DialogMatchParasAll::setMatchParas()
{
	//set patches match parameters 
	Params::shape_context_sample_point_num = atoi((ui.lineEdit_shape_context_sample_point_num->text()).toStdString().c_str());

	



}

void DialogMatchParasAll::getMatchParas()
{
	ui.lineEdit_shape_context_sample_point_num->setText(QString::fromStdString(to_string(Params::shape_context_sample_point_num)));
	ui.lineEdit_shape_context_bending_weight->setText(QString::fromStdString(to_string(Params::shape_context_bending_weight)));
	ui.lineEdit_shape_context_match_weight->setText(QString::fromStdString(to_string(Params::shape_context_match_weight)));
	ui.lineEdit_shape_context_appearance_weight->setText(QString::fromStdString(to_string(Params::shape_context_appearance_weight)));
	ui.lineEdit_shape_context_use_rotation->setText(QString::fromStdString(to_string(Params::shape_context_use_rotation)));
	ui.lineEdit_shape_context_compare_1_thres->setText(QString::fromStdString(to_string(Params::shape_context_compare_1_thres)));
	ui.lineEdit_shape_context_compare_2_thres->setText(QString::fromStdString(to_string(Params::shape_context_compare_2_thres)));

	ui.lineEdit_surf_descriptor_min->setText(QString::fromStdString(to_string(Params::surf_descriptor_min)));
	ui.lineEdit_surf_compare_1_thres->setText(QString::fromStdString(to_string(Params::surf_compare_1_thres)));
	ui.lineEdit_surf_compare_2_thres->setText(QString::fromStdString(to_string(Params::surf_compare_2_thres)));
	ui.lineEdit_surf_dimensions->setText(QString::fromStdString(to_string(Params::surf_dimensions)));
	ui.lineEdit_surf_min_ratio->setText(QString::fromStdString(to_string(Params::surf_min_ratio)));
}

void DialogMatchParasAll::on_OKbtn_matchParasAll()
{
	setMatchParas();
	this->close();
}