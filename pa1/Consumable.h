#ifndef _Consumable_included_
#define _Consumable_included_

#include "Item.h"
#include "Character.h"
#include <string>

class Consumable : public Item
{
public:
	Consumable();
	
	int getQuantity();
	void setQuantity(int iQuantity);

	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void use(Character & user, int iNum);

private:
	int m_iQuantity;
};

#endif
