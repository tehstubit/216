#include "Equipment.h"

using namespace std;

Equipment::Equipment()
{
	m_bEquipped = false;
}

string Equipment::getSlot()
{
	return m_sSlot;
}

void Equipment::setSlot(string sSlot)
{
	m_sSlot = sSlot;
}

void Equipment::dumpObjectData()
{
	Item::dumpObjectData();
	//cout << "	-Slot: " << m_sSlot << endl;
	return;
}

void Equipment::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
	output << "<slot>" << m_sSlot << "</slot>" << endl;
	return;
}

void Equipment::setElementData(string sElementName, string sValue)
{
	if (sElementName == "slot")
		m_sSlot = atoi(sValue.c_str());
	else
		Item::setElementData(sElementName, sValue);
}
	
void Equipment::setEquipped(bool bEquipped)
{	
	m_bEquipped = bEquipped;
}

bool Equipment::getEquipped()
{
	return m_bEquipped;
}
