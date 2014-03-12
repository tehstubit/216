#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <functional>
#include <map>
#include <cstdlib>
#include <vector>
#include <csignal>

#include "Armor.h"
#include "Creature.h"
#include "Weapon.h"
#include "Item.h"
#include "XMLSerializable.h"

using namespace std;


//void setContent(string sElementName, string sContent, vector<XMLSerializable*>& vObjects, int i);

void parseElement(istream & input, string sPrefix, XMLSerializable * pObject, vector<XMLSerializable*>& vObjects, map<string,function<XMLSerializable*()>> & mapConstructor, int &iPosition)
{
	string sElementName;
	getline(input, sElementName, '>');

	if( sElementName.back() == '/' )
	{
		cout << sPrefix << "Empty element: " << sElementName << endl;
		return;
	}
	else
	{	
		if( sElementName == "Item" || sElementName == "Weapon" || sElementName == "Armor" || sElementName == "Creature")
		{
			function<XMLSerializable*()> pFunc = mapConstructor[sElementName];
			XMLSerializable* xmlObject = pFunc();
			vObjects.push_back(xmlObject);
			iPosition++;
		} 
	}

	string sContent = "";

	while( true )
	{

		char c = input.get();

		while( c != '<' )
		{
			if( c != '\n' )
				sContent.push_back(c);

			c = input.get();
		}

		if( input.peek() == '/' )
		{
			input.get();
			string sEndElement;
			getline(input, sEndElement, '>');

			if( sEndElement != sElementName )
				cout << "Bad XML found" << endl;

			vObjects[iPosition]->setElementData(sElementName, sContent);
			return;
		}
		else
		{
			parseElement(input, sPrefix + " > " + sElementName, pObject, vObjects, mapConstructor, iPosition);
		}

	}

}

//void setContent(string sElementName, string sContent, vector<XMLSerializable*>& vObjects, int i)
//{
//	
//	if( sElementName == "name" ) 
//		vObjects[i]->setName(sContent);
//	else if (sElementName == "weight")
//		vObjects[i]->setWeight(atoi(sContent.c_str()));
//	else if (sElementName == "symbol")
//	{
//		char* cContent;
//		strcpy(cContent, sContent.c_str());
//		vObjects[i]->setSymbol(*cContent);
//	}
//	else if (sElementName == "value")
//		vObjects[i]->setValue(atoi(sContent.c_str()));
//	else if (sElementName == "health")
//		vObjects[i]->setHealth(atoi(sContent.c_str()));
//	else if (sElementName == "hostile")
//		vObjects[i]->setHostile((sContent == "true"));
//	else if (sElementName == "attackBonus")
//		vObjects[i]->setAttackBonus(atoi(sContent.c_str()));
//	else if (sElementName == "weaponType")
//		vObjects[i]->setWeaponType(atoi(sContent.c_str()));
//	else if(sElementName == "defenseBonus")
//		vObjects[i]->setDefenseBonus(atoi(sContent.c_str()));
//
//	return;
//}

void parseXML(string sFilename, vector<XMLSerializable*>& vObjects, map<string, function<XMLSerializable*()>>& mapConstructor)
{
	ifstream input;
	input.open(sFilename);

	while( input.get() != '?' );
	while( input.get() != '?' );
	
	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );

	int iCounter = -1;
	
	parseElement(input, "> ", NULL, vObjects, mapConstructor, iCounter);
	
}

int main(int argc, char * argv[])
{
	cout << "What file should we parse? ";
	string sFilename;
	cin >> sFilename;
	cout << endl;

	vector<XMLSerializable*> vObjects;
	map<string, function<XMLSerializable*()>> mapConstructor;
	mapConstructor["Item"] = []() { return new Item;};
	mapConstructor["Creature"] = []() { return new Creature;};
	mapConstructor["Weapon"] = []() { return new Weapon;};
	mapConstructor["Armor"] = []() { return new Armor;};
	parseXML(sFilename, vObjects, mapConstructor);	
	
	ofstream output;
	string sOutputFile;
	cout << "What should we name the new XML file? ";
	cin >> sOutputFile;
	output.open(sOutputFile);
	output << "<?xml version='1.0' encoding='utf-8'?>" << endl;
	output << "<World>" << endl;

	for(int i = 0; i < vObjects.size(); i++)
	{
		vObjects[i]->dumpObject();
		vObjects[i]->writeFragment(output);
		output << endl;
	}

	output << "</World>" << endl;

	return 0;
}
