#include "Entity.h"
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <string>
#include "Creature.h"

using namespace std;

Entity::Entity()
{
	m_cSymbol = 'X';
}

void Entity::setName(string sName)
{
	m_sName = sName;
}

string Entity::getName()
{
	return m_sName;
}

void Entity::setSymbol(char cSymbol)
{
	m_cSymbol = cSymbol;
}

char Entity::getSymbol()
{
	return m_cSymbol;
}

void Entity::setCoords(int x, int y)
{
	m_iX = x;
	m_iY = y;
}

void Entity::setX(int x)
{
	m_iX = x;
}

void Entity::setY(int y)
{
	m_iY = y;
}

int Entity::getX()
{
	return m_iX;
}

int Entity::getY()
{
	return m_iY;
}

void Entity::dumpObject()
{
	return;
}

void Entity::dumpObjectData()
{
	stringstream ss;
	ss  << "	-Name: " << getName() << endl;
	addstr(ss.str().c_str());
	//cout << "	-Symbol: " << getSymbol() << endl;
	return;
}

void Entity::writeDataAsFragment(ostream & output)
{
	output << "<name>" << m_sName << "</name>" << endl;
	output << "<symbol>" << m_cSymbol << "</symbol>" << endl;
	return;
}

void Entity::setElementData(string sElementName, string sValue)
{	
	if (sElementName == "name")
		m_sName = sValue;

	else if (sElementName == "symbol")
		m_cSymbol = sValue.at(0);
		
	
}

