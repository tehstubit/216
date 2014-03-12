#include "Weapon.h"

#include <cstdlib>

using namespace std;

Weapon::Weapon(void)
{
	m_iAttackBonus = 0;
	m_iWeaponType = 0;
}


Weapon::~Weapon(void)
{
}


void Weapon::dumpObject()
{
	cout << "Weapon:" << endl;
	dumpObjectData();
}

void Weapon::dumpObjectData()
{
	Equipment::dumpObjectData();

	cout << "   [AttackBonus] " << getAttackBonus() << endl;
	cout << "    [WeaponType] " << getWeaponType() << endl;
}

void Weapon::writeFragment(ostream & output)
{
	output << "   <Weapon>" << endl;
	writeDataAsFragment(output);
	output << "   </Weapon>" << endl;
}

void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output << "      <attackBonus>" << getAttackBonus() << "</attackBonus>" << endl;
	output << "      <weaponType>" << getWeaponType() << "</weaponType>" << endl;
}

void Weapon::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);

	if( sElementName == "attackBonus" )
	{
		setAttackBonus(atoi(sValue.c_str()));
	}
	else if( sElementName == "weaponType" )
	{
		setWeaponType(atoi(sValue.c_str()));
	}
}


int Weapon::getAttackBonus()
{
	return m_iAttackBonus;
}

void Weapon::setAttackBonus(int iAttackBonus)
{
	m_iAttackBonus = iAttackBonus;
}

int Weapon::getWeaponType()
{
	return m_iWeaponType;
}

void Weapon::setWeaponType(int iWeaponType)
{
	m_iWeaponType = iWeaponType;
}

