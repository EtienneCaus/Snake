#include "snake.h"
#include <iostream>

void Snake::print()
{
    printf("\033[%d;%dH", position[0], position[1]);    //put the cursor at position
    printf("%c", c);                //print the character
}
void Snake::print(char c)
{
    printf("\033[%d;%dH", position[0], position[1]);
    printf("%c", c);                //print the character
}

void Snake::move(int x, int y)
{
    position[0]+=y;
    position[1]+=x;
};

void Snake::check_position(int x, int y)
{
    if(position[0] > y)    //check if position is larger than tableau
       position[0] = 0;
    if(position[0] < 0)     //check if position is lower thatn minimum (0)
        position[0] = y;

    if(position[1] > x)     //même chose avec la largeur
        position[1] = 0;    //fait le tours
    if(position[1] < 0)
        position[1] = x;
};

void Snake::set_position(int x, int y)
{
    position[0]=y;
    position[1]=x;
};

int Snake::get_positionX()
{
    return position[1];
};
int Snake::get_positionY()
{
    return position[0];
};

bool Snake::isHead()
{
    if(id==0)
        return true;
    else
        return false;
}

Snake::Snake(int id, int x, int y)
{
    this->id=id;
    //if(id%2!=0)
    //    c='o';
    position[0]=y;
    position[1]=x;
}

Snake::Snake(int x, int y)
{
    this->id=0;
    this->c='@';
    position[0]=y;
    position[1]=x;
}