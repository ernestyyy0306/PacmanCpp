#include "Maze.h"
Maze::Maze(){

};
Maze::~Maze(){

};
void Maze::Import_Map(){
    fstream readfile;
        readfile.open("Maze3.txt",ios::in);
        if(!readfile.is_open())
            {cout<<"Cannot open file."<<endl;}
        else{
            for(int row=0;row<height;row++){
                for(int column=0;column<width;column++){
                    readfile>>maze[row][column];
                    if(maze[row][column]=='!'){maze[row][column]=' ';}
		}	}	}
};
void Maze::Display_Map(char input[height][width]){ //added color console
	 HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_SCREEN_BUFFER_INFO csbi;
	 GetConsoleScreenBufferInfo(hstdout, &csbi);
	 for (int row = 0; row < height; row++) {
		 for (int column = 0; column < width; column++) {
			 if (input[row][column] == '.') {
				 SetConsoleTextAttribute(hstdout, 0x0E);
				 cout << input[row][column];
				 SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			 }
			 else if (input[row][column] == '#') {
				 SetConsoleTextAttribute(hstdout, 0x01);
				 cout << input[row][column];
				 SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			 }
			 else {
				 cout << input[row][column];
			 }
		 }
		cout << endl;	
	 }
};
void Maze::Copy_Layout(char input[height][width]){
    memcpy(input,maze,sizeof(maze));
};
void Display(char input[height][width]){
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE); // added color console
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
    for(int row=0;row<height;row++){
            for(int column=0;column<width;column++){
				if (input[row][column] == '.') {
					SetConsoleTextAttribute(hstdout, 0x0E);
					cout << input[row][column];
					SetConsoleTextAttribute(hstdout, csbi.wAttributes);
				}
				else if (input[row][column] == '#') {
					SetConsoleTextAttribute(hstdout, 0x01);
					cout << input[row][column];
					SetConsoleTextAttribute(hstdout, csbi.wAttributes);
				}
				else {
					cout << input[row][column];
				}

			}
            cout<<endl;
	}
};
