#include "Creature.h"

using namespace std;

Creature::Creature()
{
	// Such a hostile world...
	m_bHostile = true;
}

bool Creature::isHostile()
{
	return m_bHostile;
}

void Creature::setHostile(bool bHostile)
{
	m_bHostile = bHostile;
}

void Creature::attack(Player * target)
{	
	int iAttackPower = Character::getHealth()/3 + 1;
	int iDefense = target->getDefense();
	if(target->getEquippedArmor() != NULL)
		iDefense = iDefense + target->getEquippedArmor()->getDefenseBonus();
	int iDamage = iAttackPower - iDefense;
	if(iDamage >= 1)
		target->setHealth(target->getHealth() - iDamage);
	else
		target->setHealth(target->getHealth() - 1);
}

void Creature::dumpObject()
{
	cout << "Creature:" << endl;
	dumpObjectData();
	return;
}
void Creature::dumpObjectData()
{
	Character::dumpObjectData();
	cout << "	-Hostile: " << m_bHostile << endl;
	return;
}

void Creature::writeFragment(ostream & output)
{
	output << "<Creature>" << endl;
	writeDataAsFragment(output);
	output << "</Creature>" << endl;
	return;
}

void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output << "<hostile>" << m_bHostile << "</hostile>" << endl;
	return;
}

void Creature::setElementData(string sElementName, string sValue)
{
	if (sElementName == "hostile")
		m_bHostile = (sValue == "true" || sValue == "1");
	else 
		Character::setElementData(sElementName, sValue);
	
}

void Creature::movePlayer(int iPlayerX, int iPlayerY, vector< vector<Tile> > vTiles, Entity* player, vector<Entity*> vCreatures)
{
	bool bBlocked = false;
	if(isHostile())
	{
		if(iPlayerX < Entity::getX() && vTiles[Entity::getY()][Entity::getX() -1].getPassable() )
		{
			for(auto it : vCreatures)
			{
				if(it->getX() == Entity::getX()-1 && it->getY() == Entity::getY())
					bBlocked = true;
			}
			if(!bBlocked)
			{	
				if(!(Entity::getX()-1 == iPlayerX && Entity::getY() == iPlayerY))
					Entity::setX(Entity::getX() -1);
				
				else
					attack(dynamic_cast<Player*>(player));
			}
		}
		
		else if(iPlayerX > Entity::getX() && vTiles[Entity::getY()][Entity::getX() + 1].getPassable() )
		{
			for(auto it : vCreatures)
			{
				if(it->getX() == Entity::getX()+1 && it->getY() == Entity::getY())
					bBlocked = true;
			}
			if(!bBlocked)
			{	
				if (!(Entity::getX()+1 == iPlayerX && Entity::getY() == iPlayerY))
						Entity::setX(Entity::getX() + 1);
				else
					attack(dynamic_cast<Player*>(player));
			}
		}

		else if(iPlayerY < Entity::getY() && vTiles[Entity::getY()-1][Entity::getX()].getPassable() )
		{
			for(auto it : vCreatures)
			{
				if(it->getX() == Entity::getX() && it->getY() == Entity::getY()-1)
					bBlocked = true;
			}
			if(!bBlocked)
			{	
				if(!(Entity::getX() == iPlayerX && Entity::getY()-1 == iPlayerY))
					Entity::setY(Entity::getY()-1);
				else
					attack(dynamic_cast<Player*>(player));
			}
		}
		
		else if(iPlayerY > Entity::getY() && vTiles[Entity::getY()+1][Entity::getX()].getPassable() )
		{
			for(auto it : vCreatures)
			{
				if(it->getX() == Entity::getX() && it->getY() == Entity::getY()+1)
					bBlocked = true;
			}
			if(!bBlocked)
			{	
				if( !(Entity::getY()+1 == iPlayerY && Entity::getX() == iPlayerX))
					Entity::setY(Entity::getY() +1);
				else
					attack(dynamic_cast<Player*>(player));	
			}
		}
	}
}
