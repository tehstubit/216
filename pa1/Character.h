#ifndef _Character_included_
#define _Character_included_

#include "Item.h"
#include "Entity.h"
#include "Dungeon.h"
#include <vector>

class Character : public Entity
{
public:
	Character();
	int getHealth();
	void setHealth(int iHealth);
	std::vector<Item*>  getInventory();
	void setInventory(Item* item);
	void generateInventory();
	void removeItem(int iNum);
	void setMaxHealth(int iHealth);
	int getMaxHealth();

	virtual void attack(Character & target);

	virtual void dumpObject() {}
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output) {}
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual void drop(Dungeon &dLevel);
private:
	int m_iHealth;
	int m_iMaxHealth;
	std::vector<Item*> m_vInventory;
	
};

#endif
