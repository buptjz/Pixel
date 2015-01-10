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
	//Params::shape_context_sample_point_num = atoi((ui.lineEdit_shape_context_sample_point_num->text()).toStdString().c_str());
	string shape_context_sample_point_num = (ui.lineEdit_shape_context_sample_point_num->text()).toStdString();
	string shape_context_bending_weight = (ui.lineEdit_shape_context_bending_weight->text()).toStdString();
	string shape_context_match_weight = (ui.lineEdit_shape_context_match_weight->text()).toStdString();
	string shape_context_appearance_weight = (ui.lineEdit_shape_context_appearance_weight->text()).toStdString();
	string shape_context_use_rotation = (ui.lineEdit_shape_context_use_rotation->text()).toStdString();
	string shape_context_compare_1_thres = (ui.lineEdit_shape_context_compare_1_thres->text()).toStdString();
	string shape_context_compare_2_thres = (ui.lineEdit_shape_context_compare_2_thres->text()).toStdString();
	string top_k = (ui.lineEdit_top_k->text()).toStdString();
	Params::set_attr("shape_context_sample_point_num", shape_context_sample_point_num.c_str());
	Params::set_attr("shape_context_bending_weight", shape_context_bending_weight.c_str());
	Params::set_attr("shape_context_match_weight", shape_context_match_weight.c_str());
	Params::set_attr("shape_context_appearance_weight", shape_context_appearance_weight.c_str());
	Params::set_attr("shape_context_use_rotation", shape_context_use_rotation.c_str());
	Params::set_attr("shape_context_compare_1_thres", shape_context_compare_1_thres.c_str());
	Params::set_attr("shape_context_compare_2_thres", shape_context_compare_2_thres.c_str());
	Params::set_attr("top_k", top_k.c_str());

	string surf_descriptor_min = (ui.lineEdit_surf_descriptor_min->text()).toStdString();
	string surf_compare_1_thres = (ui.lineEdit_surf_compare_1_thres->text()).toStdString();
	string surf_compare_2_thres = (ui.lineEdit_surf_compare_2_thres->text()).toStdString();
	string surf_dimensions = (ui.lineEdit_surf_dimensions->text()).toStdString();
	string surf_min_ratio = (ui.lineEdit_surf_min_ratio->text()).toStdString();
	Params::set_attr("surf_descriptor_min", surf_descriptor_min.c_str());
	Params::set_attr("surf_compare_1_thres", surf_compare_1_thres.c_str());
	Params::set_attr("surf_compare_2_thres", surf_compare_2_thres.c_str());
	Params::set_attr("surf_dimensions", surf_dimensions.c_str());
	Params::set_attr("surf_min_ratio", surf_min_ratio.c_str());
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
	ui.lineEdit_top_k->setText(QString::fromStdString(to_string(Params::top_k)));
}

void DialogMatchParasAll::on_OKbtn_matchParasAll()
{
	setMatchParas();
	this->close();
}