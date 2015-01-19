#ifndef DIALOG_CATEGORY_H
#define DIALOG_CATEGORY_H

#include <QWidget>
#include "ui_dialog_category.h"
#include <string>
using namespace std;
class DialogCategory : public QDialog
{
	Q_OBJECT

public:
	DialogCategory(QWidget *parent = 0);
	~DialogCategory();
	string getCategory();
	void setCategory(string category);
	Ui::DialogCategory ui;
	string category;
signals:
	void sig(string);
public slots:
	void on_SaveCategoryBtn();

};

#endif