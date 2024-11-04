#include <iostream>
#include <chrono>
#include <list>
#include <curses.h>

#include "snake.h"
using namespace std;
using namespace std::chrono;

void wait(int time);
const int tableau[2] = {25,50}; //grandeur de la carte

int main()
{
    initscr();              //initialise l'écran
    curs_set(0);            //hide the cursor
    
    int newPosition[2]={0,0};   //utilisé pour bouger le corps du serpent
    int oldPosition[2]={0,0};
    int movement=3;         //met le mouvement à 3 (droite)

    list<Snake> snake;      //fabrique le serpent
    Snake head(5,5);        //fabrique la tête (id 0)
    snake.push_back(head);
    snake.push_back(Snake(snake.size(),3,5));   //met deux autres corps
    snake.push_back(Snake(snake.size(),4,5));

    cout << "\033[2J\033[1;1H"; // clears screen
    int pomme[2]={25,10};   //emplacement de la pomme

    while(true)
    {       
        nodelay(stdscr,TRUE);   //needed so getch won't stop the program
        int input = getch();    //take input
        fflush(stdin);          //flush the inputs to prevent overflow
        printf("\033[%d;%dH", pomme[1], pomme[0]);    //put the cursor at pomme
        cout << "\033[1;31m";   //set text color to red
        printf("Ç");                                 //dessine la pomme
        cout << "\033[0m";   //set text color to default

        switch (input)
        {
        case 'w':
            if(movement != 2)
                movement=0; //move the head
        break;
        case 'a':
            if(movement != 3)
                movement=1;
        break;
        case 's':
            if(movement != 0)
                movement=2;
        break;
        case 'd':
            if(movement != 1)
                movement=3;
        break;
        }

        for(Snake& s : snake)
        {
            if(s.isHead())  //check it the reference is the head
            {
                newPosition[1]=head.get_positionX();    //set new position to the head
                newPosition[0]=head.get_positionY();

                switch (movement)
                {
                case 0:
                    head.move(0,-1); //move the head
                break;
                case 1:
                    head.move(-1,0);
                break;
                case 2:
                    head.move(0,1);
                break;
                case 3:
                    head.move(1,0);
                break;
                }
                
                head.check_position(tableau[1], tableau[0]);
                head.print();   //show the head
            }
            else            //if the reference is a body...
            {
                s.print(' ');   //erase the body
                oldPosition[1] = s.get_positionX(); //take the old position
                oldPosition[0] = s.get_positionY();
                s.set_position(newPosition[1],newPosition[0]);  //set new position
                newPosition[1] = oldPosition[1];    //set new position for next body
                newPosition[0] = oldPosition[0];
                s.print();                          // show the body
            }
        }

        if(head.get_positionX() == pomme[0] && head.get_positionY() == pomme[1])    //si la tête touche une pomme
        {
            snake.push_back(Snake(snake.size(),newPosition[1],newPosition[0]));     //...ajoute un corps
            pomme[0] = rand() % tableau[1]; //met la pomme à un endroit au hazard
            pomme[1] = rand() % tableau[0];
        }

        for(Snake& s : snake)
        {
            if(head.get_positionX() == s.get_positionX() && head.get_positionY() == s.get_positionY() && !s.isHead())
            {
                printf("\033[%d;%dH", 0, 0);    //put the cursor at position 0,0
                cout << "Score : " << snake.size() << " GAME OVER!\n";
                cin.ignore();
                cin.get();
                endwin();   //end the uses of ncurses
                return false;
            }
        }    

        printf("\033[%d;%dH", 0, 0);    //put the cursor at position 0,0
        cout << "Score : " << snake.size();
        printf("\033[%d;%dH", 0, 0);    //put the cursor at position 0,0... again
        fflush(stdout); //needed to print stuff
        wait(5);      //wait 5 something
    } 

    return 0;
}

void wait(int time)
{
    time *= 10000000; // makes the timer longer
	auto interval = seconds(time).count(); //set the interval(int) to the timer(seconds)

	while (interval != 0)   //decreases the interval to simulate time
		interval--;
};