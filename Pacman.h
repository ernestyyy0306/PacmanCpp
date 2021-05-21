#ifndef PACMAN_H
#define PACMAN_H
#include "Setting.h"


class Pacman {
private:
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
	int x, y;
	int pSpeed;
	int score, pLoop;
	char Direction;
	char Turning_To;
	char temp_map[height][width];
public:
	Pacman();
	Pacman(char input[height][width]);
	~Pacman();
	void setposition(int x, int y);
	void Input();
	void Logic();
	void WormHole();
	void PacPos(int* in_x, int* in_y);
	void InitialPos();
	void PacStart();
	void reload_map(char input[height][width]);
	void Reset();
	void Get_Layout(char input[height][width]);
	void Giv_Score(int* in_score);
	void Debug();
};

#endif
