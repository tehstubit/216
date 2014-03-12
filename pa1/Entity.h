#ifndef _Entity_included_
#define _Entity_included_

#include <vector>
#include <ostream>
#include <string>
#include <iostream>
#include "XMLSerializable.h"
#include "Tile.h"
#include <sstream>
#include <ncurses.h>

class Entity : public XMLSerializable
{
public:
	Entity();
	std::string getName();
	void setName(std::string sString);
	char getSymbol();
	void setSymbol(char cSymbol);
	void setCoords(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output) {}
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual void movePlayer(int iPlayerX, int iPlayerY, std::vector<std::vector<Tile> > vTiles, Entity* player, std::vector<Entity*> vCreatures) {}
	virtual void drop() {}

	
private:
	std::string m_sName;
	char m_cSymbol;
	int m_iX;
	int m_iY;
};

#endif

