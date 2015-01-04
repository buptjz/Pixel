#include "logDisplay.h"
#include "qt_pixel_main.h"
#include <qstring.h>
#include "tools.h"
#include "params.h"
#include <QtWidgets/QMainWindow>

void LogDisplay::logDisplay(string logstr)
{
#ifdef __DEBUG__
		logstr = getTime() + " " + logstr;
		logQstr = QString::fromStdString(logstr);

		//QString existStr = qt_Pixel_Main::ui.LogDisplay->toPlainText();
		//logQstr = existStr.append("\n").append(logQstr);
		//logQstr.append("\n");
	    //qt_Pixel_Main::ui.LogDisplay->setText(logQstr);
		//qt_Pixel_Main::ui.LogDisplay->moveCursor(QTextCursor::End);
		emit sig(logQstr);
#endif
}
