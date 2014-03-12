#include "Weapon.h"

using namespace std;

Weapon::Weapon()
{
	m_iAttackBonus = 0;
	m_iWeaponType = 0;
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

void Weapon::dumpObject()
{
	//cout << "Weapon:" << endl;
	if(Equipment::getEquipped())
		addstr("Weapon (Equipped):\n");
	else
		addstr("Weapon:\n");
	dumpObjectData();
	return;
}

void Weapon::dumpObjectData()
{
	Equipment::dumpObjectData();
	//cout << "	-AttackBonus: " << m_iAttackBonus << endl;
	//cout << "	-WeaponType: " << m_iWeaponType << endl;
	stringstream ss;
	ss <<  "	-AttackBonus: " << m_iAttackBonus << endl;
	addstr(ss.str().c_str());
	return;
}

void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output << "<attackBonus>" << m_iAttackBonus << "</attackBonus>" << endl;
	output << "<weaponType>" << m_iWeaponType << "</weaponType>" << endl;
	return;
}

void Weapon::writeFragment(ostream & output)
{
	output << "<Weapon>" << endl;
	writeDataAsFragment(output);
	output << "</Weapon>" << endl;
	return;
}

void Weapon::setElementData(string sElementName, string sValue)
{
	if (sElementName == "weaponType")
		setWeaponType(atoi(sValue.c_str()));
	else if (sElementName == "attackBonus")
		setAttackBonus(atoi(sValue.c_str()));
	else 
		Equipment::setElementData(sElementName, sValue);
}
