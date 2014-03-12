#ifndef _GenericFactory_included_
#define _GenericFactory_included_

#include "Creature.h"
#include "EntityVector.h"
#include "Item.h"
#include "Consumable.h"
#include "Weapon.h"
#include "Armor.h"
#include <vector>

class GenericFactory
{
public:	
	static GenericFactory & instance();
	virtual ~GenericFactory();
	Creature * generateCreature(int iMaxHealth);
	Item * generateItem();
	Consumable * generateConsumable();
	Weapon * generateWeapon();
	Armor * generateArmor();
private:
	GenericFactory();
	EntityVector<Creature>  m_vCreatures;
	EntityVector<Item> m_vItems;
	EntityVector<Consumable> m_vConsumables;
	EntityVector<Weapon> m_vWeapons;
	EntityVector<Armor> m_vArmor;
};

#endif
