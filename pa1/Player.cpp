#include "Player.h"
#include "Dungeon.h"
#include <string>
#include "Tools.h"
#include <ncurses.h>

using namespace std;

Player::Player() : m_iExperienceNeeded(100), m_iAttackPower(5), m_iDefense(1)
{
	m_iExperience = 0;
	m_iLevel = 1;
	m_wEquippedWeapon = NULL;
	m_aEquippedArmor = NULL;
}

int Player::getExperience()
{
	return m_iExperience;
}

void Player::setExperience(int iExperience)
{
	m_iExperience = iExperience;
}

int Player::getLevel()
{
	return m_iLevel;
}

void Player::setLevel(int iLevel)
{
	m_iLevel = iLevel;
}

void Player::attack(Character & target, stringstream & ssOutput)
{
	int iDice = Tools::randomValue(11);
	if(iDice == 0)
		ssOutput << "You missed the " << target.getName() << endl;
	else if(iDice < 10)
	{
		target.setHealth(target.getHealth() - (m_iAttackPower * (2/3)+1));
		ssOutput << "You attacked the " << target.getName() << endl;
		target.setHostile(true);
	}
	else
	{
		target.setHealth(target.getHealth() - m_iAttackPower);
		ssOutput << "You critial hit the " << target.getName() << endl;	
		target.setHostile(true);
	}
}

void Player::movePlayer(int iCommand, Dungeon dLevel, stringstream & ssOutput)
{
	vector<Entity*> creatures = dLevel.getCreatures();
	for(int i = 0; i < creatures.size(); i++)
	{
		if(creatures[i]->getX() == this->getX() && creatures[i]->getY() == this->getY()-1 && iCommand == 'w')
		{
			attack(*dynamic_cast<Character*>(creatures[i]), ssOutput);
			return;
		}
		if(creatures[i]->getX() == this->getX()-1 && creatures[i]->getY() == this->getY() && iCommand == 'a')
		{
			attack(*dynamic_cast<Character*>(creatures[i]), ssOutput);
			return;
		}
		if(creatures[i]->getX() == this->getX() && creatures[i]->getY() == this->getY()+1 && iCommand == 's')
		{
			attack(*dynamic_cast<Character*>(creatures[i]), ssOutput);
			return;
		}
		if(creatures[i]->getX() == this->getX()+1 && creatures[i]->getY() == this->getY() && iCommand == 'd')
		{
			attack(*dynamic_cast<Character*>(creatures[i]), ssOutput);
			return;
		}
		
	}
	if (iCommand == 'w')
	{
		if(dLevel.getLevel()[this->getY() - 1][this->getX()].getPassable())
			this->setY(this->getY()-1);
	}

	else if (iCommand == 'a')
	{
		if(dLevel.getLevel()[this->getY()][this->getX()-1].getPassable())
			this->setX(this->getX()-1);
	}

	else if (iCommand == 's')
	{
		if(dLevel.getLevel()[this->getY() + 1][this->getX()].getPassable())
			this->setY(this->getY()+1);
	}

	else if (iCommand == 'd')
	{
		if(dLevel.getLevel()[this->getY()][this->getX()+1].getPassable())
			this->setX(this->getX()+1);
	}		
}

void Player::pickUp(Dungeon &dLevel)
{
	Item* temp = dLevel.removeItem(Entity::getX(), Entity::getY());
	bool bPotion = false;
	Consumable* cTemp = dynamic_cast<Consumable*>(temp);
	if(cTemp != NULL)
	{
		for(auto it : Character::getInventory())
		{
			if (it->getName() == "health potion") 
			{
				it->setQuantity(cTemp->getQuantity()+it->getQuantity());
				bPotion = true;
			}
			
		}
	}
	if (!bPotion && temp != NULL)
		Character::setInventory(temp);
}

void Player::displayInventory()
{
	if(Character::getInventory().size() == 0)
	{
		addstr("You have nothing. ");
	}
	else
	{
		move(0,0);
		clear();
		for(int i=0; i < Character::getInventory().size(); i++)
		{
			stringstream ss;
			ss << i + 1 << ": ";
			addstr(ss.str().c_str());	
			Character::getInventory()[i]->dumpObject();
		}
	}
}

void Player::drop(int iInvNum, Dungeon &dLevel)
{
	Item* iTemp = Character::getInventory()[iInvNum];
	unequip(Character::getInventory()[iInvNum]);
	Character::removeItem(iInvNum);
	iTemp->setCoords(Entity::getX(), Entity::getY());
	dLevel.addItem(iTemp);
}

void Player::equip(int iInvNum, stringstream & ss)
{
	iInvNum--;
	if(dynamic_cast<Armor*>(Character::getInventory()[iInvNum]) != NULL)
	{	
		if(m_aEquippedArmor != NULL)
			m_aEquippedArmor->setEquipped(false);
		m_aEquippedArmor = dynamic_cast<Armor*>(Character::getInventory()[iInvNum]);
		Character::getInventory()[iInvNum]->setEquipped(true);
	}	
	else if(dynamic_cast<Weapon*>(Character::getInventory()[iInvNum]) != NULL)
	{
		if(m_wEquippedWeapon != NULL)
			m_wEquippedWeapon->setEquipped(false);
		m_wEquippedWeapon = dynamic_cast<Weapon*>(Character::getInventory()[iInvNum]);
		Character::getInventory()[iInvNum]->setEquipped(true);
	}
	else
	{
		ss << "You cannot equip that\n";
	}
} 

int Player::getInvSize()
{
	return Character::getInventory().size();
}

void Player::levelUp()
{
	m_iLevel++;
	m_iExperienceNeeded = m_iExperienceNeeded + m_iLevel * 100;
	m_iAttackPower = m_iAttackPower + m_iLevel;
	m_iDefense++;
	Character::setMaxHealth(Character::getMaxHealth() + m_iLevel);
	Character::setHealth(Character::getMaxHealth());
}

int Player::getExperienceNeeded()
{
	return m_iExperienceNeeded;
}

int Player::getAttackPower()
{
	return m_iAttackPower;
}

int Player::getDefense()
{
	return m_iDefense;
}

Weapon* Player::getEquippedWeapon()
{
	return m_wEquippedWeapon;
}

Armor* Player::getEquippedArmor()
{
	return m_aEquippedArmor;
}

void Player::unequip(Item* item)
{
	if (m_wEquippedWeapon == item)
	{	
		m_wEquippedWeapon = NULL;
		item->setEquipped(false);
	}
	else if(m_aEquippedArmor == item)
	{
		m_aEquippedArmor = NULL;
		item->setEquipped(false);
	}
}
