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
	void setSegmentParas();//��� dialog�ϵġ�OK����ť�� �����޸ĵĲ���
	void getSegmentParas();//����dialog����ʱ������ǰ������ʾ�ڶ�Ӧ�Ľ�������
public slots:
	void on_OKbtn_segmentParasAll();
};

#endif