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
	void setMatchParas();
};

#endif