#ifndef LOGDISPLAY_H
#define LOGDISPLAY_H
#include <string>
#include <iostream>
#include <QtCore/QThread>

using namespace std;

class LogDisplay : public QThread
{
    Q_OBJECT
public:
    LogDisplay(){};
    ~LogDisplay(){};
    QString logQstr;
public:
    void logDisplay(string logstr);
signals:
    void sig(QString);
};
#endif
