#ifndef MAZE_H
#define MAZE_H
#include "Setting.h"

class Maze{
private:
    char maze[height][width];
public:
    Maze();
    ~Maze();
    void Import_Map();
    void Display_Map(char input[height][width]);
    void Display(char input[height][width]);
    void Copy_Layout(char input[height][width]);
};


#endif
