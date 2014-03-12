#ifndef _Item_included_
#define _Item_included_

#include <string>

//
// NOTE!
//
// In the presented hierarchy, Item should inherit from Entity,
// which should have the setName functionality...
//

class Item
{
public:
	std::string getName();
	void setName(std::string sName);

private:
	std::string m_sName;
};

#endif
