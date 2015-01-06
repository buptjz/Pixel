#ifndef DIALOG_SEGMENTPARASALL_H
#define DIALOG_SEGMENTPARASALL_H

#include <QWidget>
#include "ui_dialog_segmentParasAll.h"
#include <qgraphicsscene.h>
class DialogSegmentParasAll : public QDialog
{
	Q_OBJECT

public:
	DialogSegmentParasAll(QWidget *parent = 0);
	~DialogSegmentParasAll();

private:
	Ui::DialogSegmentParasAll ui;


public:
	void setSegmentParas();//点击 dialog上的“OK”按钮， 设置修改的参数
	void getSegmentParas();//进入dialog界面时，将当前参数显示在对应的界面项里
public slots:
	void on_OKbtn_segmentParasAll();
};

#endif