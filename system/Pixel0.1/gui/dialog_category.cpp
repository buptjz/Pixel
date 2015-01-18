#include "dialog_category.h"
using namespace std;
DialogCategory::DialogCategory(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.SaveCategoryBtn, SIGNAL(clicked()), this, SLOT(on_SaveCategoryBtn()));
	
}

DialogCategory::~DialogCategory()
{
}

string DialogCategory::getCategory()
{
	string categoryStr = (ui.lineEditCategory->text()).toStdString();
	return categoryStr;
}

void DialogCategory::setCategory(string category)
{
	this->category = category;
}

void DialogCategory::on_SaveCategoryBtn()
{
	string category = getCategory();
	emit this->sig(category);
	this->close();
}