#ifndef GHOST_H
#define GHOST_H
#include "Setting.h"

class Ghost {
private:
	int gX, gY;
	int iniX, iniY;
	int x, y;
	int rX, rY;
	int gSpeed;
	int gLoop;
	int score;
	int k, l;
	int gTime;
	char old_name;
	char name;
	char Mode;
	bool update;
	bool killed;
	bool win;
	bool gEscaped;
	bool death;
	bool scatter;
	char temp_mapG[height][width];
	char temp_mapR[height][width];
	char temp_mapB[height][width];
	struct walkG {
		short walk_countG;
		short xG;
		short yG;
		short backG;
	};
	struct targetG {
		short xG;
		short yG;
	};
	vector <targetG> walk_queueG;
	vector <walkG> BFSArrayG;

public:
	Ghost();
	Ghost(char input[height][width], char ghost_name, int inPosX, int inPosY, char in_Mode);
	~Ghost();
	void setposition(int x, int y);
	void AddArrayG(int in_xG, int in_yG, int wcG, int backG);
	void FindPathG(int in_gX, int in_gY, int in_xG, int in_yG);
	void Get_PacXY(int in_x, int in_y);
	void ResetGhost(int in_x, int in_y);
	void Ghost_Start();
	void Behavior();
	void TrackPac(char input[height][width]);
	void Scatter(int in_score);
	void RNG();
	void Follow();
	void Block_wormhole();
	void Kill(bool* GG);
	void Death();
	void Log();
	void Log_Layout();
	void clear_log();
	void next_lvl();
	void Debug();
};


#endif
