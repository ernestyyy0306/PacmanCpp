#include "Ghost.h"

Ghost::Ghost(){
};
Ghost::Ghost(char input[height][width],char ghost_name,int inPosX,int inPosY,char in_Mode){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);   //for color console
	gX = inPosX; gY = inPosY;
	iniX = inPosX; iniY = inPosY;
	gTime = -1;
	x = y = 0;
	k = 0;
	l = 0;
	win = false;
	killed = false;
	score = 0;
	rX = inPosX; rY = inPosY;
	name = ghost_name;
	old_name = ghost_name;
	gSpeed = GhostSpeed;
	gLoop = 0;
	Mode = in_Mode;
	update = false;
	death = false;
	scatter = false;
    for(int row=0;row<height;row++){
        for(int column=0;column<width;column++){
            temp_mapG[row][column]=input[row][column];}}
    for(int row=0;row<height;row++){
        for(int column=0;column<width;column++){
            temp_mapB[row][column]=input[row][column];}}
};
Ghost::~Ghost(){
};
void Ghost::TrackPac(char input[height][width]){
    if(!scatter){
		for(int row=0;row<height;row++){
			for(int column=0;column<width;column++){
				temp_mapR[row][column]=input[row][column];
	}	}	}
};
void Ghost::Block_wormhole(){					
	for (int column = 0; column < width; column++) {
		if (temp_mapB[1][column] == '.' || temp_mapB[1][column] == '#') {
			temp_mapB[1][column] = '#';
			temp_mapG[1][column] = '#';
			temp_mapR[1][column] = '#';
		}
	}
	for (int column = 0; column < width; column++) {
		if (temp_mapB[height - 2][column] == '.' || temp_mapB[height - 2][column] == '#') {
			temp_mapB[height - 2][column] = '#';
			temp_mapG[height - 2][column] = '#';
			temp_mapR[height - 2][column] = '#';
		}
	}
	for (int row = 0; row < height; row++) {
		if (temp_mapB[row][1] == '.' || temp_mapB[row][1] == '#') {
			temp_mapB[row][1] = '#';
			temp_mapG[row][1] = '#';
			temp_mapR[row][1] = '#';
		}
	}
	for (int row = 0; row < height; row++) {
		if (temp_mapB[row][width - 2] == '.' || temp_mapB[row][width - 2] == '#') {
			temp_mapB[row][width - 2] = '#';
			temp_mapG[row][width - 2] = '#';
			temp_mapR[row][width - 2] = '#';
		}
	}
};
void Ghost::setposition(int x,int y){
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={x,y};
    SetConsoleCursorPosition(hStdout,position);
};
void Ghost::AddArrayG(int in_xG,int in_yG,int wcG,int backG){
    if(temp_mapG[in_yG][in_xG]==' '||temp_mapG[in_yG][in_xG]=='.'){
        temp_mapG[in_yG][in_xG]='!';
		walkG tmpG;
		tmpG.xG=in_xG;
		tmpG.yG=in_yG;
		tmpG.walk_countG=wcG;
		tmpG.backG=backG;
		BFSArrayG.push_back(tmpG);}
};
void Ghost::FindPathG(int in_gX,int in_gY,int in_xG,int in_yG){
	memcpy(temp_mapG,temp_mapR,sizeof(temp_mapR));
	BFSArrayG.clear();
	walkG tmpG;
	tmpG.xG = in_gX;
	tmpG.yG = in_gY;
	tmpG.walk_countG = 0;
	tmpG.backG = -1;
	BFSArrayG.push_back(tmpG);
	int i = 0;
	while(i<BFSArrayG.size()){
		if(BFSArrayG[i].xG == in_xG&&BFSArrayG[i].yG==in_yG){
			walk_queueG.clear();
			targetG tmp2G;
			while(BFSArrayG[i].walk_countG!=0){
				tmp2G.xG=BFSArrayG[i].xG;
				tmp2G.yG=BFSArrayG[i].yG;
				walk_queueG.push_back(tmp2G);
				i=BFSArrayG[i].backG;}
			break;}
		AddArrayG(BFSArrayG[i].xG+1,BFSArrayG[i].yG,BFSArrayG[i].walk_countG+1,i);
		AddArrayG(BFSArrayG[i].xG-1,BFSArrayG[i].yG,BFSArrayG[i].walk_countG+1,i);
		AddArrayG(BFSArrayG[i].xG,BFSArrayG[i].yG+1,BFSArrayG[i].walk_countG+1,i);
		AddArrayG(BFSArrayG[i].xG,BFSArrayG[i].yG-1,BFSArrayG[i].walk_countG+1,i);
		i++;}
	BFSArrayG.clear();
};
void Ghost::Get_PacXY(int in_x,int in_y){
    if(!scatter&&gTime<0){
        x=in_x;
        y=in_y;}
    else{
        x=in_x;
        y=in_y;
        rX=iniX;
        rY=iniY;
    }
};
void Ghost::RNG(){
    while(!scatter&&gLoop%(gSpeed*StepChg)==0){
        rX=rand()%((width-2)+1);rY=rand()%((height-2)+1);
        while(temp_mapB[rY][rX]!='.'){
            rX=rand()%((width-2)+1);rY=rand()%((height-2)+1);}break;}
};
void Ghost::Behavior(){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			if (temp_mapB[row][column] == '-') {
				temp_mapR[row][column] = ' ';
			}
		}
	}
	setposition(gX, gY);
	if (name == 'G') {
		SetConsoleTextAttribute(hstdout, 0x07);
		cout << name;
	}
	else if (name == 'S') {
		SetConsoleTextAttribute(hstdout, 0x0A);
		cout << name;
	}
	else if(name == 'B'){
		SetConsoleTextAttribute(hstdout, 0x0B);
		cout << name;
	}
	else if (name == 'I') {
		SetConsoleTextAttribute(hstdout, 0x0C);
		cout << name;
	}
	else if (name == 'C') {
		SetConsoleTextAttribute(hstdout, 0x0D);
		cout << name;
	}
	else if (name == 'F' && Mode != 'O') {
		SetConsoleTextAttribute(hstdout, 0x0E);
		cout << name;
	}
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	while(Mode=='A'){
        if(x<=width/2&&y<=height/2&&!scatter){FindPathG(gX,gY,x,y);}
        else {RNG();FindPathG(gX,gY,rX,rY);}
        break;
    }
    while(Mode=='B'){
        if(x>=width/2&&y>=height/2&&!scatter){FindPathG(gX,gY,x,y);}
        else {RNG();FindPathG(gX,gY,rX,rY);}
        break;
    }
    while(Mode=='C'){
        if(x>=width/2&&y<=height/2&&!scatter){FindPathG(gX,gY,x,y);}
        else {RNG();FindPathG(gX,gY,rX,rY);}
        break;
    }
    while(Mode=='D'){
        if(x<=width/2&&y>=height/2&&!scatter){FindPathG(gX,gY,x,y);}
        else {RNG();FindPathG(gX,gY,rX,rY);}
        break;
    }
	while (Mode == 'R') {
		RNG(); FindPathG(gX, gY, rX, rY);
		break;
	}
	while (Mode == 'Z') {
        if(!scatter){FindPathG(gX,gY,x,y);}
        else {RNG();FindPathG(gX,gY,rX,rY);}
		break;
	}
};
void Ghost::ResetGhost(int in_x,int in_y){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	if (!death) {
		gX = in_x, gY = in_y;
		walk_queueG.clear();
		setposition(gX, gY);
		if (name == 'G') {
			SetConsoleTextAttribute(hstdout, 0x07);
			cout << name;
		}
		else if (name == 'S') {
			SetConsoleTextAttribute(hstdout, 0x0A);
			cout << name;
		}
		else if (name == 'B') {
			SetConsoleTextAttribute(hstdout, 0x0B);
			cout << name;
		}
		else if (name == 'I') {
			SetConsoleTextAttribute(hstdout, 0x0C);
			cout << name;
		}
		else if (name == 'C') {
			SetConsoleTextAttribute(hstdout, 0x0D);
			cout << name;
		}
		else if (name == 'F') {
			SetConsoleTextAttribute(hstdout, 0x0E);
			cout << name;
		}
		else {
			cout << name;
		}
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	}
};
void Ghost::Kill(bool* GG){
	if (gX == x && gY == y && !death && !scatter) {
		*GG = true;
		update = true;
		killed = true;
	}
	else { *GG = false; }
};
void Ghost::Scatter(int in_score){
	score = in_score;
	if (score%RageMode == 0 && score != 0) {
		gTime = 5;
		scatter = true;
		name = 'F';
		update = true;
	}
	if (gTime > 0 && gLoop%TimerCount == 0 && !death) {
		gTime--;
	}
	if (gTime == 0) {
		scatter = false;
		rX = iniX; rY = iniY;
		gTime = -1;
		name = old_name;
		update = true;
	}
};
void Ghost::Death(){
    if(gX==x&&gY==y&&scatter){
        death=true;
		update = true;
    }
};
void Ghost::Follow() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	setposition(gX, gY);
	if (temp_mapR[gY][gX] == '.') {
		SetConsoleTextAttribute(hstdout, 0x0E);
		cout << ".";
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	}
	else if (temp_mapR[gY][gX] == ' '&&temp_mapB[gY][gX] == '.')cout << " ";
	else if (temp_mapR[gY][gX] == ' '&&temp_mapB[gY][gX] == ' ')cout << " ";
	else if (temp_mapB[gY][gX] == '-') { cout << "-"; }
	if (gLoop%gSpeed == 0 && walk_queueG.size() != 0) {
		gX = walk_queueG.back().xG;
		gY = walk_queueG.back().yG;
		walk_queueG.pop_back();
	}
};
void Ghost::Ghost_Start(){
	gLoop++;
	Block_wormhole();
	if (!death) {
		Death();
	}
	if (!death) {
		while (gLoop%gSpeed == 0 && !death) {
			Follow();
			Behavior();
			break;
		}
	}
	if (update) {
		Log();
		update = false;
	}
};
void Ghost::Debug(){
	setposition(150, 34);
	cout << "x  position: " << x << " " << endl;
	setposition(150, 35);
	cout << "y  position: " << y << " " << endl;
	setposition(150, 36);
	cout << "gX position: " << gX << " " << endl;
	setposition(150, 37);
	cout << "gY position: " << gY << " " << endl;
	setposition(150, 38);
	cout << "Ghost Timer: " << gTime << " " << endl;
	setposition(150, 39);
	cout << "Ghost Loop: " << gLoop << " " << endl;
	setposition(150, 40);
	cout << "RNG X: " << rX << " " << endl;
	setposition(150, 41);
	cout << "RNG Y: " << rY << " " << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setposition(50 + j, 40 + i);
			cout << temp_mapR[i][j];
		}
		cout << endl;
	}
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			setposition(149+j,45+i);
			cout<<temp_mapB[i][j];}
		cout<<endl;}
};
void Ghost::Log_Layout() {
	setposition(70, 1);
	cout << "*---------------------------------------------------------*";
	setposition(70, 39);
	cout << "*---------------------------------------------------------*";
	for (int i = 2; i < 39; i++) {
		setposition(70, i);
		cout << "|                                                         |";
	}
	setposition(71, 2);
	cout << "Instructions: ";
	setposition(71, 4);
	cout << "   Press W to go up";
	setposition(71, 5);
	cout << "   Press A to go left";
	setposition(71, 6);
	cout << "   Press S to go down";
	setposition(71, 7);
	cout << "   Press D to go right";
	setposition(71, 9);
	cout << "   Eat all the pallets before the time limit to proceed";
	setposition(71, 10);
	cout << "   Don't let the ghost catch you";

	setposition(71, 12);
	cout << "Game Log:";
	setposition(71, 30);
	cout << "Notice:";
};
void Ghost::Log() {
	static int Log_Line = 14;
	if (death && k == 0) {
		setposition(71, Log_Line);
		cout << "   You killed " << old_name << "!!!";
		Log_Line++; k++;
	}
	if (scatter && !death&&Mode == 'O'&&l == 0) {
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);
		setposition(71, Log_Line);
		SetConsoleTextAttribute(hstdout, 0x74);
		cout << "   FRENZY MODE!!!!";
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		Log_Line++; l++;
	}
	if (gTime == -1 && Mode == 'O' && !win) {
		setposition(71, Log_Line);
		cout << "   Frenzy stopped...";
		Log_Line++; l = 0;
	}
	if (Log_Line == 29) {
		Log_Line = 14;
		clear_log();
	}
	if (win&&Mode == 'O') {
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);
		setposition(71, Log_Line);
		SetConsoleTextAttribute(hstdout, 0x02);
		cout << "   Congratulations! Proceed to next level!";
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		Log_Line++;
		win = false;
	}
	if (killed) {
		setposition(71, Log_Line);
		cout << "   Too bad! You had been eaten!";
		Log_Line++;
		killed = false;
	}
};
void Ghost::clear_log() {
	for (int i = 14; i < 30; i++) {
		setposition(71, i);
		cout << "                                                         ";
	}
}
void Ghost::next_lvl() {
	gSpeed -= 20;
	death = false;
	k = 0;
	scatter = false;
	name = old_name;
	gTime = -1;
	win = true;
	Log();
}