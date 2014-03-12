#ifndef _Entity_included_
#define _Entity_included_

#include "XMLSerializable.h"

#include <vector>

class Entity :
	public XMLSerializable
{
public:
	Entity(void);
	virtual ~Entity(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual std::string getName();
	virtual void setName(std::string sName);
	virtual char getSymbol();
	virtual void setSymbol(char cSymbol);

private:
	std::string m_sName;
	char m_cSymbol;
};

#endif