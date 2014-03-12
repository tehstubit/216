#include "Consumable.h"

using namespace std;

Consumable::Consumable()
{
	m_iQuantity = 1;
}

int Consumable::getQuantity()
{
	return m_iQuantity;
}

void Consumable::setQuantity(int iQuantity)
{
	m_iQuantity = iQuantity;
}

void Consumable::use(Character & user, int iNum)
{
	if(user.getHealth() + 5 < user.getMaxHealth())
		user.setHealth(user.getHealth() + 5);
	else
		user.setHealth(user.getMaxHealth());
	m_iQuantity--;
	if(m_iQuantity == 0)
	{
		user.removeItem(iNum);
	}
}

void Consumable::setElementData(string sElementName, string sValue)
{
	if (sElementName == "quantity")
		setQuantity(atoi(sValue.c_str()));
	else
		Item::setElementData(sElementName, sValue);
}

void Consumable::dumpObject()
{
	addstr("Consumable:\n");
	dumpObjectData();
	return;
}

void Consumable::dumpObjectData()
{
	Item::dumpObjectData();
	stringstream ss;
	ss  << "	-Quantity: " << m_iQuantity << endl;
	addstr(ss.str().c_str());
	return;
}
