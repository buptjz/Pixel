#ifndef LOGDISPLAY_H
#define LOGDISPLAY_H
#include <string>
#include <iostream>

using namespace std;

class LogDisplay
{
public:
	LogDisplay(){};
	~LogDisplay(){};
	string logQstr;
public:
	void logDisplay(string logstr);
	void sig(string);
};

#endif