#ifndef _XMLSerializable_included_
#define _XMLSerializable_included_

#include <iostream>
#include <string>

class XMLSerializable
{
public:
	XMLSerializable(void);
	virtual ~XMLSerializable(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
};


#endif
