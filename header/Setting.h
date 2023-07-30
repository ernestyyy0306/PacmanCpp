#ifndef SETTING_H
#define SETTING_H
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <time.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
#define _WIN32_WINNT 0x502
#define width 67
#define height 41
#define PacX 33
#define PacY 30
#define PacSpeed 100
#define GhostSpeed 200
#define TimerCount 2000
#define RageMode 200
#define StepChg 12
#define logowidth 136
#define logoheight 11 
#define arrowX 60
#define arrowY 17
#define cursorX 60
#define cursorY 17
#define chooseX 60
#define chooseY 17
#define creditX1 47
#define creditY1 21
#define creditX2 54
#define creditY2 21
#define hsX1 47
#define hsY1 14
#define hsX2 54
#define hsY2 14
#define playerSize 10
//debug GhostSpeed 5 PacSpeed 1 TimerCount 10
//Normal GhostSpeed 500 PacSpeed 200 TimerCount 4000

class Setting {
public:
	void setposition(int x, int y);
	void ShowConsoleCursor(bool showFlag);
	void maximizeWindow();
	void countdown();
};

#endif // SETTING_H_INCLUDED
