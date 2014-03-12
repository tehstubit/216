#ifndef _Creature_included_
#define _Creature_included_

#include "Character.h"
#include <vector>
#include "Tile.h"
#include "Player.h"

class Creature : public Character
{
public:
	Creature();
	~Creature() {}
	bool isHostile();
	void setHostile(bool bHostile);
	void movePlayer(int iPlayerX, int iPlayerY, std::vector<std::vector<Tile> > vTiles, Entity* player, std::vector<Entity*> vCreatures);

	virtual void attack(Player * target);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
private:
	bool m_bHostile;
};

#endif

