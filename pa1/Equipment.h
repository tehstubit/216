#ifndef _Equipment_included_
#define _Equipment_included_

#include "Item.h"
#include <string>

class Equipment : public Item
{
public:
	std::string getSlot();
	void setSlot(std::string sSlot);
	Equipment();
	~Equipment() {}
	virtual void dumpObject() {}
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output) {}
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	void setEquipped(bool bEquipped);
	bool getEquipped();
private:
	std::string m_sSlot;
	bool m_bEquipped;
};

#endif
