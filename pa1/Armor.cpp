#include "Armor.h"

using namespace std;

Armor::Armor()
{
	m_iDefenseBonus = 0;
}

int Armor::getDefenseBonus()
{
	return m_iDefenseBonus;
}

void Armor::setDefenseBonus(int iDefenseBonus)
{
	m_iDefenseBonus = iDefenseBonus;
}

void Armor::dumpObject()
{
	if(Equipment::getEquipped())
		addstr("Armor (Equipped):\n");
	else
		addstr("Armor:\n");
	dumpObjectData();
	return;
}

void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();
	stringstream ss;
	ss  << "	-DefenseBonus: " << m_iDefenseBonus << endl;
	addstr(ss.str().c_str());
	return;
}

void Armor::writeFragment(ostream & output)
{
	output << "<Armor>" << endl;
	writeDataAsFragment(output);
	output << "</Armor>" << endl;
	return;
}

void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output << "<defenseBonus>" << m_iDefenseBonus << "</defenseBonus>" << endl;
	return;
}

void Armor::setElementData(string sElementName, string sValue)
{
	if (sElementName == "defenseBonus")
		m_iDefenseBonus = atoi(sValue.c_str());
	else
		Equipment::setElementData(sElementName, sValue);
}
