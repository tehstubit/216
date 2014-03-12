#ifndef _XMLSerializable_included_
#define _XMLSerializable_included_

#include <iostream>
#include <string>

class XMLSerializable
{
public:
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual void setName(std::string sName) {};
	virtual void setWeight(int iWeight) {};
	virtual void setSymbol(char cSymbol) {};
	virtual void setValue(int iValue) {};
	virtual void setHealth(int iHealth) {};
	virtual void setHostile(bool bHostile) {};
	virtual void setAttackBonus(int iAttackBonus) {};
	virtual void setWeaponType(int iWeaponType) {};
	virtual void setDefenseBonus(int iDefenseBonus) {};
};


#endif
