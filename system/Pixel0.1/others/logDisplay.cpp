#include "logDisplay.h"
#include "tools.h"
#include "params.h"

void LogDisplay::logDisplay(string logstr){
#ifdef __DEBUG__
    logstr = getTime() + "  " + logstr;
    cout << logstr << endl;
#endif
}
