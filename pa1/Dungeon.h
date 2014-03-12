#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <vector>
#include "Tile.h"
#include <random>
#include <cmath>
#include "Item.h"

class Dungeon
{
public:
	Dungeon();
	void createLevel(std::mt19937 &mt);
	bool checkCreatures();
	void outputLevel(int iPlayerX, int iPlayerY);
	std::vector< std::vector<Tile> > getLevel();
	void generateItems();
	void generateCreatures(int iLevel);
	void findUpstairs(int &x, int &y);
	void moveCreatures(int iPlayerX, int iPlayerY, Entity* player);
	void addItem(Item* item);
	Item* removeItem(int iX, int iY);
	void outputItems();
	void findDownstairs(int &x, int &y);
	std::vector<Entity*> getCreatures();
	void Reveal(std::vector<std::vector<Tile>> & level, char cSymbol, int iX, int iY);
private:
	std::vector< std::vector<Tile> > m_vLevel;
	std::vector<Item*> m_vItems;
	std::vector<Entity*> m_vCreatures;
};

#endif
