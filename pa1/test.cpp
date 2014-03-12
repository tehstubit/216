#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include <ctime>
#include <random>
#include <cstdlib>

using namespace std;



// Practicum 8 : Implement this method
void markPosition(vector<vector<Tile> > & vLevel, int x, int y)
{
	if (x >= 79 || y >= 20 || x < 0 || y < 0)
	{
		return;
	}

	if (vLevel[y][x].getSymbol() != '.' && vLevel[y][x].getSymbol() != '#' && vLevel[y][x].getSymbol() != '<' && vLevel[y][x].getSymbol() != '>')
	{
		return;
	}
	
	vLevel[y][x].setSymbol('X');
	
	markPosition(vLevel, x+1, y);
	markPosition(vLevel, x, y+1);
	markPosition(vLevel, x-1, y);
	markPosition(vLevel, x, y-1);
}


bool testLevel(vector<vector<Tile> > & vLevel)
{
	//Display the initial state
	//cout << "Initial state: " << endl;

	//cout << endl;

	int x = -1;
	int y = -1;

	// pick a starting position
	for( int i = 0; i < vLevel.size(); i++ )
	{
		for( int j = 0; j < vLevel[i].size(); j++ )
		{
			if( vLevel[i][j].getSymbol() == '.' || vLevel[i][j].getSymbol() == '#' )
			{
				// Starting position just has to be a room or
				// tunnel tile
				x = j;
				y = i;
			}
		}
	}

	if( x == -1 )
	{
		cout << "Unable to find starting position!" << endl;
		return false;
	}
	
	// Call the function which actually marks the tiles -- it should mark
	// the starting tile, then any adjacent to it, etc -- so after it's done,
	// everything that can be connected to the starting tile should be
	// marked.
	markPosition(vLevel, x, y);

	bool bCorrect = true;

	//cout << endl << "Marked state: " << endl;
	// Outer loop
	for( auto itOuter = vLevel.begin(); itOuter != vLevel.end(); itOuter++ )
	{
		// Inner loop
		for( auto itInner = (*itOuter).begin(); itInner != (*itOuter).end(); itInner++ )
		{
			//cout << (*itInner);


			// Now, test if it's a room/tunnel tile -- if it's still
			// one after we've 
			if( (*itInner).getSymbol() == '.' || (*itInner).getSymbol() == '#' )
			{
				bCorrect = false;
			}
		}

		//cout << endl;
	}

	//cout << endl;

	if( !bCorrect )
	{
		cout << "Unreached room/tunnel tile detected!" << endl;
	}

	//test for upstairs and downstairs
	bool bUpFlag = false;
	bool bDownFlag = false;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 79; j++)
		{
			if (vLevel[i][j].getSymbol == '<')
				bUpFlag = true;
			if (vLevel[i][j].getSymbol == '>')
				bDownFlag = true;
		}
	}
	
	if(!bUpFlag || !bDownFlag)
	{
		cout << "No upstairs or downstairs" << endl;
		bCorrect = false
	}

	return bCorrect;

}

int main(int argc, char * argv[])
{	
	mt19937 mt;
	mt.seed(time(NULL));

	if( argc == 1)
	{
		Dungeon level;
		level.createLevel(mt);
		vector<vector<Tile> > vTiles = level.getLevel();
		if(testLevel(vTiles))
			cout << "Test completed successfully." << endl;
	}

	else
	{
		bool bFlag = true;

		for(int i = 0; i < atoi(argv[1]); i++)
		{
			Dungeon level;
			level.createLevel(mt);
			vector<vector<Tile> > vTiles = level.getLevel();
			if(!testLevel(vTiles))
			{
				for(int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 79; j++)
					{
						cout << vTiles[i][j].getSymbol();
					}
					cout << endl;
				}	
				cout << "Level failed 1 or more tests." << endl;
				bFlag = false;
			}
		}
		
		if(bFlag)
			cout << "All tests completed successfully" << endl;
	}

	return 0;
}
