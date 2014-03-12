#ifndef _Player_included_
#define _Player_included_

#include "Character.h"
#include "Dungeon.h"
#include <vector>
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include <sstream>

class Player : public Character
{
public:
	Player();
	int getExperience();
	void setExperience(int iExperience);
	int getLevel();
	void setLevel(int iLevel);
	void movePlayer(int iCommand, Dungeon dLevel, std::stringstream & ssOutput);
	void pickUp(Dungeon &dLevel);
	void displayInventory();
	void drop(int iInvNum, Dungeon &dLevel);
	int getInvSize();
	void levelUp();
	int getExperienceNeeded();
	int getAttackPower();
	int getDefense();
	void equip(int iInvNum, std::stringstream & ss);
	Weapon* getEquippedWeapon();
	Armor* getEquippedArmor();
	void unequip(Item* item);

	virtual void attack(Character & target, std::stringstream & ssOutput);

private:
	int m_iExperience;
	int m_iLevel;
	int m_iExperienceNeeded;
	int m_iAttackPower;
	int m_iDefense;
	Weapon* m_wEquippedWeapon;
	Armor* m_aEquippedArmor;
};

#endif

