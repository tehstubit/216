#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "Armor.h"
#include "Weapon.h"
#include "Item.h"
#include "Creature.h"

using namespace std;

XMLSerializable * constructItem()
{
	return new Item;
}

int main()
{
	map<string,function<XMLSerializable*()>> mapConstructor;
	mapConstructor["Item"] = constructItem;
	mapConstructor["Creature"] = []() { return new Creature;};
	mapConstructor["Armor"] = []() { return new Armor;};
	mapConstructor["Weapon"] = []() { return new Weapon;};

	string sLookup;
	cout << "Please enter a class to look up: "; 
	cin >> sLookup;

	function<XMLSerializable*()> pFunc = mapConstructor[sLookup];

	if(pFunc == NULL )
	{
		cout << "Nothing found" << endl;
	}
	else
	{
		pFunc();
		cout << "Found a valid function" << endl;
	}

	return 0;
}

