#pragma once

class Snake
{
private:
    int id=0;
    int position[2]={0,0};
    char c='O';
public:
    void print();
    void print(char c);
    void move(int x, int y);
    void check_position(int x, int y);
    void set_position(int x, int y);
    int get_positionX();
    int get_positionY();
    bool isHead();
    Snake(int id, int x, int y);
    Snake(int x, int y);
};