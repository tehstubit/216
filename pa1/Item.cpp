#include "Item.h"

using namespace std;

Item::Item()
{
	m_iWeight = 0;
	m_iValue = 0;
}

void Item::setWeight(int iWeight)
{
	m_iWeight = iWeight;
}

int Item::getWeight()
{
	return m_iWeight;
}

void Item::setValue(int iValue)
{
	m_iValue = iValue;
}

int Item::getValue()
{
	return m_iValue;
}

void Item::dumpObject()
{
	cout << "Item:" << endl;
	dumpObjectData();
	return;
}

void Item::dumpObjectData()
{
	Entity::dumpObjectData();
	//cout << "	-Weight: " << m_iWeight << endl;
	//cout << "	-Value: " << m_iValue << endl;
	return;
}

void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output << "<weight>" << m_iWeight << "</weight>" << endl;
	output << "<value>" << m_iValue << "</value>" << endl;
	return;
}

void Item::writeFragment(ostream & output)
{
	output << "<Item>" << endl;
	writeDataAsFragment(output);
	output << "</Item>" << endl;
}

void Item::setElementData(string sElementName, string sValue)
{
	if (sElementName == "value")
		m_iValue = atoi(sValue.c_str());
	else if (sElementName == "weight")
		m_iWeight = atoi(sValue.c_str());
	else
		Entity::setElementData(sElementName, sValue);
}
