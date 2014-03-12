#include "CreatureFactory.h"
#include "parser.h"
#include "Armor.h"
#include "Consumable.h"
#include "Creature.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "Weapon.h"
#include "XMLSerializable.h"

#include <functional>
#include <random>
#include <ctime>

using namespace std;


CreatureFactory & CreatureFactory::instance()
{
	static CreatureFactory factory;
	return factory;
}

CreatureFactory::CreatureFactory()
{
	map<string, function<XMLSerializable*()>> mConstructors;
	mConstructors["Item"] = [] () { return new Item; };
	mConstructors["Consumable"] =  [] () { return new Consumable; };
	mConstructors["Creature"] =  [] () { return new Creature; };
	mConstructors["Weapon"] = [] () { return new Weapon; };
	mConstructors["Armor"] = [] () { return new Armor; };

	vector<XMLSerializable*> vObjects;
	
	parseXML(mConstructors, "critters.xml", vObjects);

	for (auto pObjects : vObjects)
	{
		m_vCreatures.push_back(dynamic_cast<Creature*> (pObjects));
	}

	cout << "Constructor called" << endl;
}

CreatureFactory::~CreatureFactory()
{
	cout << "Destructor called" << endl;
}

int CreatureFactory::randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}

Creature * CreatureFactory::generateCreature(int iMaxHealth)
{
	vector<Creature*> vUsable;

	for (auto pCritter : m_vCreatures)
	{
		if (pCritter->getHealth() < iMaxHealth)
		{
			vUsable.push_back(pCritter);
		}
	}
	
	if (vUsable.size() == 0)
		return NULL;

	return new Creature(*vUsable[randomValue(vUsable.size())]);
}
