#ifndef _Character_included_
#define _Character_included_

#include "Entity.h"

class Character :
	public Entity
{
public:
	Character(void);
	virtual ~Character(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual int getHealth();
	virtual void setHealth(int iHealth);

	virtual void attack(Character & target);

private:
	int m_iHealth;

};

#endif

