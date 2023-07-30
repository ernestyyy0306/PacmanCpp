#include "Setting.h"

void Setting::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
};
void Setting::maximizeWindow() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
};
void Setting::setposition(int x, int y) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x,y };
	SetConsoleCursorPosition(hStdout, position);
};
void Setting::countdown() {
	setposition(28, 19);
	cout << "           ";
	setposition(28, 20);
	cout << "     3     ";
	setposition(28, 21);
	cout << "           ";
	Sleep(1000);
	setposition(28, 19);
	cout << "           ";
	setposition(28, 20);
	cout << "     2     ";
	setposition(28, 21);
	cout << "           ";
	Sleep(1000);
	setposition(28, 19);
	cout << "           ";
	setposition(28, 20);
	cout << "     1     ";
	setposition(28, 21);
	cout << "           ";
	Sleep(1000);
	setposition(28, 19);
	cout << "           ";
	setposition(28, 20);
	cout << "    Go!    ";
	setposition(28, 21);
	cout << "           ";
	Sleep(1000);
};