#include "Pacman.h"

Pacman::Pacman(){
};
Pacman::Pacman(char input[height][width]){
    x=PacX;
    y=PacY;
    pSpeed=PacSpeed;
    score=0;
    pLoop=0;
    Direction='0';
    for(int row=0;row<height;row++){
        for(int column=0;column<width;column++){
            temp_map[row][column]=input[row][column];}}
};
Pacman::~Pacman(){
};
void Pacman::reload_map(char input[height][width]) {
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			temp_map[row][column] = input[row][column];
		}
	}
}
void Pacman::setposition(int x,int y){
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={x,y};
    SetConsoleCursorPosition(hStdout,position);
};
void Pacman::Input(){
    if(_kbhit()){
        switch(_getch()){
        case 'a':{dir=LEFT;break;}
        case 'w':{dir=UP;break;}
        case 'd':{dir=RIGHT;break;}
        case 's':{dir=DOWN;break;}
        case 'A':{dir=LEFT;break;}
        case 'W':{dir=UP;break;}
        case 'D':{dir=RIGHT;break;}
        case 'S':{dir=DOWN;break;}}}
};
void Pacman::Logic(){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
    switch (dir){
        case LEFT:{
            if(temp_map[y][x-1]=='.'||temp_map[y][x-1]==' ')
            Direction='L';Turning_To='L';break;}
        case RIGHT:{
            if(temp_map[y][x+1]=='.'||temp_map[y][x+1]==' ')
            Direction='R';Turning_To='R';break;}
        case UP:{
            if(temp_map[y-1][x]=='.'||temp_map[y-1][x]==' ')
            Direction='U';Turning_To='U';break;}
        case DOWN:{
            if(temp_map[y+1][x]=='.'||temp_map[y+1][x]==' ')
            Direction='D';Turning_To='D';break;}
        default:{break;}
    }
    if(temp_map[y][x-1]=='.'&&Direction=='L'){
				SetConsoleTextAttribute(hstdout, 0x0E);  //for color console
                setposition(x-1,y);x--;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x+1,y);cout<<' ';
                temp_map[y][x+1]=' ';score++;}
    else if(temp_map[y][x-1]==' '&&Direction=='L'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x-1,y);x--;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x+1,y);cout<<' ';
                temp_map[y][x+1]=' ';}
    else if(temp_map[y][x+1]=='.'&&Direction=='R'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x+1,y);x++;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x-1,y);cout<<' ';
                temp_map[y][x-1]=' ';score++;}
    else if(temp_map[y][x+1]==' '&&Direction=='R'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x+1,y);x++;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x-1,y);cout<<' ';
                temp_map[y][x-1]=' ';}
    else if(temp_map[y-1][x]=='.'&&Direction=='U'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x,y-1);y--;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x,y+1);cout<<' ';
                temp_map[y+1][x]=' ';score++;}
    else if(temp_map[y-1][x]==' '&&Direction=='U'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x,y-1);y--;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x,y+1);cout<<' ';
                temp_map[y+1][x]=' ';}
    else if(temp_map[y+1][x]=='.'&&Direction=='D'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x,y+1);y++;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x,y-1);cout<<' ';
                temp_map[y-1][x]=' ';score++;}
    else if(temp_map[y+1][x]==' '&&Direction=='D'){
				SetConsoleTextAttribute(hstdout, 0x0E);
                setposition(x,y+1);y++;cout<<'O';
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                setposition(x,y-1);cout<<' ';
                temp_map[y-1][x]=' ';}
};
void Pacman::WormHole(){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	if (x == 0 ) {
		setposition(x, y); cout << ' ';
		SetConsoleTextAttribute(hstdout, 0x0E);
		setposition(width - 2, y); cout << 'O';
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		x = width - 2;
	}
	else if (x == width-1) {
		setposition(x, y); cout << ' ';
		SetConsoleTextAttribute(hstdout, 0x0E);
		setposition(1, y); cout << 'O';
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		x = 1;
	}
	else if (y == 0) {
		setposition(x, y); cout << ' ';
		SetConsoleTextAttribute(hstdout, 0x0E);
		setposition(x, height-2); cout << 'O';
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		y = height-2;
	}
	else if (y == height - 1) {
		setposition(x, y); cout << ' ';
		SetConsoleTextAttribute(hstdout, 0x0E);
		setposition(x, 1); cout << 'O';
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		y = 1;
	}
};
void Pacman::PacPos(int* in_x,int* in_y){
    *in_x=x;
    *in_y=y;
};
void Pacman::InitialPos(){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, 0x0E);
    setposition(x,y);cout<<"O";
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
};
void Pacman::PacStart(){
    Input();
    pLoop++;
    while(pLoop%pSpeed==0){
        Input();
        Logic();
        WormHole();
        break;
    }
	setposition(71, 33); cout << "   Score: " << score << "    " << endl;
};
void Pacman::Get_Layout(char input[height][width]){
    memcpy(input,temp_map,sizeof(temp_map));
};
void Pacman::Giv_Score(int* in_score){
    *in_score=score;
};
void Pacman::Reset(){
    x=PacX;
    y=PacY;
    Direction='0';
    dir=STOP;
};
void Pacman::Debug(){
    setposition(59,33);
    cout<<"Direction: "<<Direction<<" "<<endl;
    setposition(59,34);
    cout<<"Turning to "<<Turning_To<<" "<<endl;
    setposition(59,35);
    cout<<"x position: "<<x<<" "<<endl;
    setposition(59,36);
    cout<<"y position: "<<y<<" "<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            setposition(58+j,i);
            cout<<temp_map[i][j];}
        cout<<endl;}
};
