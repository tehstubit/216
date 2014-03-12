#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include <ncurses.h>

#include "DungeonLevel.h"

using namespace std;

int main(int argc, char * argv[])
{
	mt19937 mt;
	mt.seed( time(NULL) );
	initscr();
	keypad(stdscr, TRUE);
	stringstream ssHolder;
	int iCommand;
	string sCommand;
	int iX = 6;
	int iY = 3;
	int iTurn = 1;
	char cCommand = 'c';

	while(iCommand != 'q')
	{
		DungeonLevel dl(79, 20, mt);

		if (iCommand ==	KEY_DOWN)
		{
			sCommand = "Down";
			iY += 1;
		}

		else if (iCommand == KEY_LEFT)
		{
			sCommand = "Left";
			iX -= 1;
		}

		else if (iCommand == KEY_RIGHT)
		{
			sCommand = "Right";
			iX += 1;
		}

		else if (iCommand == KEY_UP)
		{
			sCommand = "Up";
			iY -= 1;
		}
	
		else
			sCommand = static_cast<char>(iCommand);	
		
		for( size_t x = 0; x < dl.getWidth(); x++ ) 
		{ 
			for( size_t y = 0; y < dl.getHeight(); y++ ) 
			{ 
				move(y,x); 
				addch(dl.at(x,y)); 
			} 
		}
		
		ssHolder.str("");
		ssHolder << iTurn << " " <<  sCommand;
		move(20, 0);
		addstr(ssHolder.str().c_str());
		refresh();
		iTurn++;
		iCommand = getch(); 
		clear();
	} 
	endwin();
	cout << "Game ended on turn " << iTurn << endl;;
	return 0;
}
