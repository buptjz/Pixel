#include "logDisplay.h"
#include "qt_pixel_main.h"
#include <qstring.h>
#include "tools.h"
#include <QtWidgets/QMainWindow>
void logDisplay(string logstr, bool debug)
{
	if (debug){
		logstr = getTime() + "  " + logstr;
		QString logQstr = QString::fromStdString(logstr);
		
		//ui.LogDisplay->setText(logQstr);
		//Ui::qt_PixelClass ui.ImageLibPath->setText(logQstr);
		QString existStr = qt_Pixel_Main::ui.LogDisplay->toPlainText();
		logQstr = existStr.append("\n").append(logQstr);
		qt_Pixel_Main::ui.LogDisplay->setText(logQstr);
		qt_Pixel_Main::ui.LogDisplay->moveCursor(QTextCursor::End);
	}	
}

