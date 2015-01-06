#ifndef DIALOG_MATCHPARASALL_H
#define DIALOG_MATCHPARASALL_H

#include <QWidget>
#include "ui_dialog_matchParasAll.h"
#include <qgraphicsscene.h>
class DialogMatchParasAll : public QDialog
{
	Q_OBJECT

public:
	DialogMatchParasAll(QWidget *parent = 0);
	~DialogMatchParasAll();

private:
	Ui::DialogMatchParasAll ui;


public:
	void setMatchParas();//点击 dialog上的“OK”按钮， 设置修改的参数
	void getMatchParas();//进入dialog界面时，将当前参数显示在对应的界面项里

public slots:
	void on_OKbtn_matchParasAll();

};


#endif