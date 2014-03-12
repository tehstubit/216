#include "Tile.h"
#include "Dungeon.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int main()
{
	Dungeon level;

	mt19937 mt;
	mt.seed( time(NULL));

	level.createLevel(mt);
	level.outputLevel();

	return 0;
}
