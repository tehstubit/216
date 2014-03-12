#ifndef _Item_included_
#define _Item_included_

#include "Entity.h"

class Item : public Entity
{
public:
	Item();
	int getWeight();
	void setWeight(int iWeight);
	int getValue();
	void setValue(int iValue);

	virtual void dumpObject();
	virtual void dumpObjectData();	
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual int getQuantity() {}
	virtual void setQuantity (int iQuantity) {}
	virtual void setEquipped(bool bEquipped) {}
	virtual bool getEquipped() {}

private:
	int m_iWeight;
	int m_iValue;
};

#endif
