#include "Character.h"
#include "GenericFactory.h"

using namespace std;

Character::Character()
{
	m_iHealth = 10;
	m_iMaxHealth = 10;
}

int Character::getHealth()
{
	return m_iHealth;
}

void Character::setHealth(int iHealth)
{
	m_iHealth = iHealth;
}

void Character::attack(Character & target)
{
}

void Character::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "	-Health: " << m_iHealth << endl;
	return;
}

void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output << "<health>" << m_iHealth << "</health>" << endl;
	return;
}

void Character::setElementData(string sElementName, string sValue)
{
	if (sValue == "health")
		m_iHealth = atoi(sValue.c_str());
	else
		Entity::setElementData(sElementName, sValue);
}

void Character::drop(Dungeon &dLevel)
{
	for (auto it : m_vInventory)
	{
		it->setCoords(Entity::getX(), Entity::getY());
		dLevel.addItem(it);
	}

	m_vInventory.clear();
}

void Character::generateInventory()
{
	int iRdm = Tools::randomValue(3);
	Item * pItem;
	if (iRdm == 0)
		pItem = GenericFactory::instance().generateConsumable();
	else if (iRdm == 1)
		pItem = GenericFactory::instance().generateWeapon();
	else if (iRdm == 2)
		pItem = GenericFactory::instance().generateArmor();
	
	m_vInventory.push_back(pItem);
}

vector<Item*> Character::getInventory()
{
	return m_vInventory;
}

void Character::setInventory(Item * item)
{
	m_vInventory.push_back(item);
}

void Character::removeItem(int iNum)
{
	m_vInventory.erase(m_vInventory.begin() + iNum);
}

int Character::getMaxHealth()
{
	return m_iMaxHealth;
}

void Character::setMaxHealth(int iNum)
{
	m_iMaxHealth = iNum;
}
