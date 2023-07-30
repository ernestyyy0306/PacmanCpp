#include "Maze.h"
#include "Pacman.h"
#include "Setting.h"
#include "Ghost.h"

using namespace std;

int menu_item = 0, Cx = cursorX, Cy = cursorY, Ax = arrowX, Ay = arrowY, loop = 0;
bool running = true;
char logo[logoheight][logowidth] = {
	"                                                                                                                                      ",
	"       ##########                   ########       ######        #######                   ####       ####     ######     ###      ### ",
	"     ###########                    #########     ########     ###########                 #####     #####    ########    ####     ### ",
	"   ###### ####                      ###    ###   ###    ###   ####     ####                ### ##   ## ###   ###    ###   #####    ### ",
	"  ###########      _     _     _    ###    ###   ###    ###   ###                          ###  ## ##  ###   ###    ###   ### ##   ### ",
	" ##########       |_|   |_|   |_|   ##########   ##########   ###             ##########   ###   ###   ###   ##########   ###  ##  ### ",
	"  ###########                       #########    ##########   ###             ##########   ###   ###   ###   ##########   ###   ## ### ",
	"   ###########                      ###          ###    ###   ####     ####                ###         ###   ###    ###   ###    ##### ",
	"     ###########                    ###          ###    ###    ###########                 ###         ###   ###    ###   ###     #### ",
	"       ##########                   ###          ###    ###      #######                   ###         ###   ###    ###   ###      ### ",
	"                                                                                                                                       "
};
struct PlayerData {
	string name;
	int Rscore;
};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);		// used for goto
COORD CursorPosition;									// used for goto

HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);       // used for color console

void maximizeWindow();
void gotoXY(int, int);									// function defined below if this is new to you.
void ShowConsoleCursor(bool);
void ShowLogo();
void ShowChoose();
void ShowArrow();
void DownButton();
void UpButton();
void EnterButton();
void OpenCreditFile();
void ShowCreditArrow();
void printHS();
void ShowHSArrow();
void changeHS(int temp_score);


int main()
{
	maximizeWindow();
	ShowConsoleCursor(false);
	ShowLogo();
	while (running) {
		loop++;
		ShowChoose();
		ShowArrow();
		Sleep(100);
		DownButton();
		UpButton();
		EnterButton();
	}
	return 0;
}

void maximizeWindow() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void ShowLogo() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	for (int i = 0; i < logoheight; i++) {
		for (int j = 0; j < logowidth; j++) {
			SetConsoleTextAttribute(hstdout, 0x0E);
			cout << logo[i][j];
		}
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		cout << endl;
	}
}

void ShowChoose() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	gotoXY(chooseX, chooseY);  SetConsoleTextAttribute(hstdout, 0x09); cout << "START GAME"; SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	gotoXY(chooseX, chooseY + 1); SetConsoleTextAttribute(hstdout, 0x09); cout << "HIGH SCORES"; SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	gotoXY(chooseX, chooseY + 2); SetConsoleTextAttribute(hstdout, 0x09); cout << "CREDIT"; SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	gotoXY(chooseX, chooseY + 3); SetConsoleTextAttribute(hstdout, 0x09); cout << "QUIT"; SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}

void ShowArrow() {
	if (Cy == cursorY) { Ax = arrowX + 10; }
	if (Cy == cursorY + 1) { Ax = arrowX + 11; }
	if (Cy == cursorY + 2) { Ax = arrowX + 6; }
	if (Cy == cursorY + 3) { Ax = arrowX + 4; }
	if (loop <= 5) {
		gotoXY(Cx - 3, Cy); cout << "   ";
		gotoXY(Ax, Ay); cout << "                ";
		gotoXY(Cx - 3, Cy); cout << "-";
		gotoXY(Cx - 2, Cy); cout << ">";
		gotoXY(Ax + 1, Ay); cout << "<";
		gotoXY(Ax + 2, Ay); cout << "-";
	}
	else {
		gotoXY(Cx - 3, Cy); cout << "   ";
		gotoXY(Ax, Ay); cout << "                ";
		gotoXY(Cx - 2, Cy); cout << "-";
		gotoXY(Cx - 1, Cy); cout << ">";
		gotoXY(Ax + 2, Ay); cout << " ";
		gotoXY(Ax, Ay); cout << "<";
		gotoXY(Ax + 1, Ay); cout << "-";
		if (loop >= 10) { loop = 0; }
	}
}

void DownButton() {
	if (GetAsyncKeyState(VK_DOWN) && Ay != cursorY + 3) //down button pressed
	{
		gotoXY(Cx - 3, Cy); cout << "   ";
		gotoXY(Ax, Ay); cout << "             ";
		Ay++;
		Cy++;
		gotoXY(Cx - 3, Cy); cout << "->";
		gotoXY(Ax + 1, Ay); cout << "<-              ";
		gotoXY(Cx - 3, Cy - 1); cout << "   ";
		gotoXY(Ax, Ay - 1); cout << "             ";
		menu_item++;
	}
}

void UpButton() {
	if (GetAsyncKeyState(VK_UP) && Ay != cursorY) //up button pressed
	{
		gotoXY(Cx - 3, Cy); cout << "   ";
		gotoXY(Ax, Ay); cout << "             ";
		Ay--;
		Cy--;
		gotoXY(Cx - 3, Cy); cout << "->";
		gotoXY(Ax + 1, Ay); cout << "<-              ";
		gotoXY(Cx - 3, Cy + 1); cout << "   ";
		gotoXY(Ax, Ay + 1); cout << "             ";
		menu_item--;
	}
}

void EnterButton() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;				//for color console
	GetConsoleScreenBufferInfo(hstdout, &csbi);		//for color console
	if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
		switch (menu_item) {

		case 0: {
			system("cls");
			srand(time(NULL));
			bool GameOver = false;
			char temp_map[height][width];
			int temp_x = 0, temp_y = 0;
			int timer = 200, loop = 0;
			int temp_score = 0;
			int Lives = 3;
			int lvl = 1;
			int i = 0;
			Setting setting;
			setting.maximizeWindow();
			setting.ShowConsoleCursor(false);
			Maze maze;
			maze.Import_Map();
			maze.Copy_Layout(temp_map);
			Pacman pacman(temp_map);
			Ghost Global(temp_map, ' ',NULL,NULL, 'O');
			Global.Get_PacXY(temp_x, temp_y);
			Global.Log_Layout();
			Ghost ghost(temp_map, 'G', 35, 20, 'Z');
			ghost.Get_PacXY(temp_x, temp_y);
			Ghost Slimey(temp_map, 'S', 31, 20, 'A');
			Slimey.Get_PacXY(temp_x, temp_y);
			Ghost Blinky(temp_map, 'B', 32, 20, 'B');
			Blinky.Get_PacXY(temp_x, temp_y);
			Ghost Inky(temp_map, 'I', 33, 20, 'C');
			Inky.Get_PacXY(temp_x, temp_y);
			Ghost Clyde(temp_map, 'C', 34, 20, 'D');
			Clyde.Get_PacXY(temp_x, temp_y);
			SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			while (Lives > 0) {
				timer = 200;
				setting.setposition(71, 32);
				cout << "   Level: " << lvl << "   ";
				setting.setposition(71, 33);
				cout << "   Score: ";
				setting.setposition(71, 34);
				cout << "   Timer: " << timer << "    ";
				setting.setposition(71, 35);
				cout << "   Lives: " << Lives << "    ";
				pacman.Get_Layout(temp_map);
				setting.setposition(0, 0);
				maze.Display_Map(temp_map);
				setting.countdown();			
				setting.setposition(0, 0);		
				maze.Display_Map(temp_map);
				pacman.Reset();
				pacman.InitialPos();     
				ghost.ResetGhost(35, 20);
				Slimey.ResetGhost(31, 20);
				Blinky.ResetGhost(32, 20);
				Inky.ResetGhost(33, 20);
				Clyde.ResetGhost(34, 20); 
				while (!GameOver) {
					pacman.PacStart();
					pacman.Giv_Score(&temp_score);
					pacman.PacPos(&temp_x, &temp_y);
					pacman.Get_Layout(temp_map);
					Global.TrackPac(temp_map);
					Global.Block_wormhole();
					Global.Get_PacXY(temp_x, temp_y);
					Global.Kill(&GameOver);
					Global.Ghost_Start();
					Global.Scatter(temp_score);
					if (timer <= 200) {
						ghost.TrackPac(temp_map);
						ghost.Block_wormhole();
						ghost.Get_PacXY(temp_x, temp_y);
						ghost.Kill(&GameOver);
						ghost.Ghost_Start();
						ghost.Scatter(temp_score);
						if (GameOver) {
							Lives--; GameOver = false; break;
						}
					}
					else {
						ghost.ResetGhost(35, 20);
					}
					if (timer <= 200) {
						Slimey.TrackPac(temp_map);
						Slimey.Block_wormhole();
						Slimey.Get_PacXY(temp_x, temp_y);
						Slimey.Kill(&GameOver);
						Slimey.Ghost_Start();
						Slimey.Scatter(temp_score);
						if (GameOver) {
							Lives--; GameOver = false; break; }
					}
					else {
						Slimey.ResetGhost(31, 20);
					}
					if (timer <= 200) {
						Blinky.TrackPac(temp_map);
						Blinky.Block_wormhole();
						Blinky.Get_PacXY(temp_x, temp_y);
						Blinky.Kill(&GameOver);
						Blinky.Ghost_Start();
						Blinky.Scatter(temp_score);
						if (GameOver) {
							Lives--; GameOver = false; break; }
					}
					else {
						Blinky.ResetGhost(32, 20);
					}
					if (timer <= 200) {
						Inky.TrackPac(temp_map);
						Inky.Block_wormhole();
						Inky.Get_PacXY(temp_x, temp_y);
						Inky.Kill(&GameOver);
						Inky.Ghost_Start();
						Inky.Scatter(temp_score);
						if (GameOver) {
							Lives--; GameOver = false; break; }
					}
					else {
						Inky.ResetGhost(33, 20);
					}
					if (timer <= 200) {
						Clyde.TrackPac(temp_map);
						Clyde.Block_wormhole();
						Clyde.Get_PacXY(temp_x, temp_y);
						Clyde.Kill(&GameOver);
						Clyde.Ghost_Start();
						Clyde.Scatter(temp_score);
						if (GameOver) {
							Lives--; GameOver = false; break; }
					}
					else {
						Clyde.ResetGhost(34, 20);
					}
					loop++;
					if (loop % 1500 == 0) { timer--; }
					setting.setposition(71, 32);
					cout << "   Level: " << lvl << "   ";
					setting.setposition(71, 34);
					cout << "   Timer: " << timer << "    ";
					setting.setposition(71, 35);
					cout << "   Lives: " << Lives << "    ";
					if (timer == 0) {
						GameOver = true;
					}
					if (temp_score % 1002 == 0) {
						i = 0;
					}
					if (temp_score % 1003 == 0 && i == 0 && temp_score != 0) {
						Global.next_lvl();
						ghost.next_lvl();
						Slimey.next_lvl();
						Blinky.next_lvl();
						Inky.next_lvl();
						Clyde.next_lvl();
						maze.Import_Map();
						maze.Copy_Layout(temp_map);
						pacman.reload_map(temp_map);
						i++; lvl++;
						break;
					}
				}

			}
			while (1) {
				setting.setposition(28, 19);
				cout << "           ";
				setting.setposition(28, 20);
				SetConsoleTextAttribute(hstdout, 0x74);
				cout << " GameOver! ";
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
				setting.setposition(28, 21);
				cout << "           ";
				Sleep(1000);
				break;
			}
			system("cls");
			changeHS(temp_score);
			ShowLogo();
			break;
		}

		case 1: {
			system("cls");
			printHS();
			Sleep(50);
			ShowHSArrow();
			system("cls");
			ShowLogo();
			break;
		}

		case 2: {
			system("cls");
			OpenCreditFile();
			Sleep(50);
			ShowCreditArrow();
			system("cls");
			ShowLogo();
			break;
		}

		case 3: {
			gotoXY(chooseX, chooseY + 4);
			cout << "The program has now terminated!!" << endl;
			running = false;
		}
		}
	}
}

void OpenCreditFile() {
	char text;
	ifstream readCredit;
	readCredit.open("Credit.txt", ios::in);
	if (!readCredit) {
		cout << "Cannot open CREDIT." << endl;
	}
	else {
		while (!readCredit.eof()) {
			readCredit >> noskipws >> text;
			cout << text;
		}
	}
	readCredit.close();
}

void ShowCreditArrow() {
	int loop2 = 0;
	while (!GetAsyncKeyState(VK_RETURN)) {
		loop2++;
		if (loop2 <= 5000) {
			gotoXY(creditX1, creditY1); cout << "-> ";
			gotoXY(creditX2, creditY2); cout << " <-";
		}
		else {
			gotoXY(creditX1, creditY1); cout << " ->";
			gotoXY(creditX2, creditY2); cout << "<- ";
			if (loop2 == 10000) {
				loop2 = 0;
			}
		}
	}
}

void printHS() {
	PlayerData arr[playerSize];
	fstream readHS;
	int tempHS = 0;
	readHS.open("Highscores.txt", ios::out | ios::in);
	if (!readHS) {
		cout << "Cannot open HIGH SCORES." << endl;
	}
	for (int p = 0; p < playerSize; p++) {
		readHS >> arr[p].name >> arr[p].Rscore;
	}
	gotoXY(26, 2);
	cout << "HIGH SCORES:";
	for (int i = 0; i < playerSize; i++) {
		gotoXY(26, 3 + i);
		cout << i + 1 << ".";
	}
	gotoXY(hsX1 + 3, hsY1);
	cout << "BACK";
	for (int w = 0; w < playerSize; w++) {
		if (w != 9) {
			gotoXY(28, w + 3);
			cout << arr[w].name;
			gotoXY(hsX1, w + 3);
			cout << arr[w].Rscore;
		}
		else {
			gotoXY(29, w + 3);
			cout << arr[w].name;
			gotoXY(hsX1, w + 3);
			cout << arr[w].Rscore;
		}
	}
	readHS.close();
}

void ShowHSArrow() {
	int loop3 = 0;
	while (!GetAsyncKeyState(VK_RETURN)) {
		loop3++;
		if (loop3 <= 5000) {
			gotoXY(hsX1, hsY1); cout << "-> ";
			gotoXY(hsX2, hsY2); cout << " <-";
		}
		else {
			gotoXY(hsX1, hsY1); cout << " ->";
			gotoXY(hsX2, hsY2); cout << "<- ";
			if (loop3 == 10000) {
				loop3 = 0;
			}
		}
	}
}

void changeHS(int temp_score) {
	PlayerData arr[playerSize];
	PlayerData tempH;
	PlayerData tempL;
	PlayerData newP;
	fstream readHS;
	readHS.open("Highscores.txt", ios::out | ios::in);
	if (!readHS) {
		cout << "Cannot open HIGH SCORES." << endl;
	}
	for (int p = 0; p < playerSize; p++) {
		readHS >> arr[p].name >> arr[p].Rscore;
	}
	readHS.close();
	if (temp_score > arr[playerSize - 1].Rscore) {
		system("cls");
		Sleep(200);
		cout << "Enter your name (without spacing): ";
		cin >> tempH.name;
		while (!GetAsyncKeyState(VK_RETURN)) {
			Sleep(20);
		}
		Sleep(200);
		tempH.Rscore = temp_score;
		for (int p = 0; p < playerSize; p++) {
			if (tempH.Rscore > arr[p].Rscore) {
				tempL.name = arr[p].name;
				tempL.Rscore = arr[p].Rscore;
				arr[p].name = tempH.name;
				arr[p].Rscore = tempH.Rscore;
				tempH.name = tempL.name;
				tempH.Rscore = tempL.Rscore;
			}
		}

		readHS.open("Highscores.txt", ios::out | ios::trunc);
		if (!readHS) {
			cout << "Cannot open HIGH SCORES." << endl;
		}
		readHS.close();
		readHS.open("Highscores.txt", ios::out | ios::in);
		if (!readHS) {
			cout << "Cannot open HIGH SCORES." << endl;
		}
		for (int p = 0; p < playerSize; p++) {
			readHS << arr[p].name << " " << arr[p].Rscore << endl;
		}
		readHS.close();
		system("cls");
		printHS();
		Sleep(200);
		ShowHSArrow();
		system("cls");
	}
	else {
		printHS();
		Sleep(200);
		ShowHSArrow();
		system("cls");
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
