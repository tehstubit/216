#include <iostream>
#include <string>
#include <vector>

using namespace std;



// Practicum 8 : Implement this method
void markPosition(vector<string> & vLevel, int x, int y)
{
	if (x >= 79 || y >= 20)
	{
		return;
	}

	if (vLevel[y][x] != '.' && vLevel[y][x] != '#')
	{
		return;
	}
	
	vLevel[y][x] = 'X';
	
	markPosition(vLevel, x+1, y);
	markPosition(vLevel, x, y+1);
	markPosition(vLevel, x-1, y);
	markPosition(vLevel, x, y-1);
}


bool testLevel(vector<string> & vLevel)
{
	// Display the initial state
	cout << "Initial state: " << endl;
	for( auto it = vLevel.begin(); it != vLevel.end(); it++ )
	{
		cout << (*it) << endl;
	}

	cout << endl;

	int x = -1;
	int y = -1;

	// pick a starting position
	for( int i = 0; i < vLevel.size(); i++ )
	{
		for( int j = 0; j < vLevel[i].size(); j++ )
		{
			if( vLevel[i][j] == '.' || vLevel[i][j] == '#' )
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

	cout << endl << "Marked state: " << endl;
	// Outer loop
	for( auto itOuter = vLevel.begin(); itOuter != vLevel.end(); itOuter++ )
	{
		// Inner loop
		for( auto itInner = (*itOuter).begin(); itInner != (*itOuter).end(); itInner++ )
		{
			cout << (*itInner);


			// Now, test if it's a room/tunnel tile -- if it's still
			// one after we've 
			if( (*itInner) == '.' || (*itInner) == '#' )
			{
				bCorrect = false;
			}
		}

		cout << endl;
	}

	cout << endl;

	if( !bCorrect )
	{
		cout << "Unreached room/tunnel tile detected!" << endl;
	}


	return bCorrect;

}

int main(int argc, char * argv[])
{
	// This code is fairly ugly, but it creates two dungeon levels, one of
	// which works, one doesn't.

	// Note that a string is *basically* a vector of chars.
	//
	// And, really, if you're going to use this code, it would work
	// out pretty well to generate a vector<string> from your dungeon
	// level...

	vector<string> vFirst;

//	vFirst.push_back("1234567890123456789012345678901234567890123456789012345678901234567890123456789");
	vFirst.push_back("                                                                               ");
	vFirst.push_back("   ........                                                                    ");
	vFirst.push_back("   ........                                          ........      .......     ");
	vFirst.push_back("   ........                                          ........######.......     ");
	vFirst.push_back("   ........                                          ........      .......     ");
	vFirst.push_back("      #                   .....          ############........      .......     ");
	vFirst.push_back("      #                   .....          #           ........         #        ");
	vFirst.push_back("      #         ##########.....          #                            #        ");
	vFirst.push_back("      #         #         .....      ..........                       #        ");
	vFirst.push_back("      #         #           #        ..........                       #        ");
	vFirst.push_back("      #    ............     #        ..........                       #        ");
	vFirst.push_back("      #####............     #########..........              ...........       ");
	vFirst.push_back("           ............              ..........              ...........       ");
	vFirst.push_back("           ............              ..........              ...........       ");
	vFirst.push_back("           ............              ..........              ...........       ");
	vFirst.push_back("                                     ..........              ...........       ");
	vFirst.push_back("                                                             ...........       ");
	vFirst.push_back("                                                             ...........       ");
	vFirst.push_back("                                                                               ");


	testLevel(vFirst);

	vector<string> vSecond;
//	vSecond.push_back("1234567890123456789012345678901234567890123456789012345678901234567890123456789");
	vSecond.push_back("    .......                                                                    ");
	vSecond.push_back("    .......  .......                                                           ");
	vSecond.push_back("    .......##.......      ..........................                           ");
	vSecond.push_back("    .......  .......      ..........................                           ");
	vSecond.push_back("             .......      ..........................     ..........            ");
	vSecond.push_back("             .......      ..........................#####..........            ");
	vSecond.push_back("                          ..........................     ..........            ");
	vSecond.push_back("                          ..........................           #               ");
	vSecond.push_back("                          ..........................           #               ");
	vSecond.push_back("                           #                                   #               ");
	vSecond.push_back("                           #                                   #               ");
	vSecond.push_back("        ........           #   ............                .......             ");
	vSecond.push_back("        ........           #   ............                .......             ");
	vSecond.push_back("        ........           #   ............    ....        .......             ");
	vSecond.push_back("        ........###############............    ....        .......             ");
	vSecond.push_back("        ........               ............####....                            ");
	vSecond.push_back("        ........               ............    ....                            ");
	vSecond.push_back("                                                                               ");
	vSecond.push_back("                                                                               ");


	testLevel(vSecond);

	return 0;
}
