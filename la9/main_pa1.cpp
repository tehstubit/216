
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

#include "XMLSerializable.h"
#include "parser.h"

#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Consumable.h"

using namespace std;




// And an example function to generate an output XML
// document given a vector of parsed objects and 
// an output stream.
void outputXML(vector<XMLSerializable*> & vObjects, 
			   ostream & output)
{
	// Write the XML header to the output
	output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;

	// Write the opening World tag (as an XML document
	// needs a root element to be valid)
	output << "<World>" << endl;

	// And iterate through the vector of objects...
	//
	// Note: If you are not familiar with iterators
	// shown here, you can, of course, use a
	// normal index based iteration 
	// (e.g., for( int i = 0, i < vObjects.size(); i++))
	// but if you're not familiar with them, they're
	// worth learning...
	//
	// Also, under g++, you need to add the -std=c++0x
	// command line argument for this to compile, due
	// to the addition of the auto keyword.
	//
	// Which is easy to do once and not worry about
	// by adding that flag to the line in your makefile
	// that compiles the .cpp files to .o files...
	for( auto it = vObjects.begin(); 
		it != vObjects.end();
		it++ )
	{
		(*it)->writeFragment(output);
	}

	// And output the end tag for the root
	// element.
	output << "</World>" << endl;

}


int main(int argc, char * argv[])
{
	cout << "What file should be used for input? ";

	string sInputFilename;
	cin >> sInputFilename;



	map<string, function<XMLSerializable*()>> mConstructors;
	mConstructors["Item"] = []() { return new Item; };
	mConstructors["Consumable"] = []() { return new Consumable; };
	mConstructors["Creature"] = []() { return new Creature; };
	mConstructors["Weapon"] = []() { return new Weapon; };
	mConstructors["Armor"] = []() { return new Armor; };

	vector<XMLSerializable*> vWorld;

	parseXML(mConstructors, sInputFilename, vWorld);


	for( auto it = vWorld.begin();
		it != vWorld.end();
		it++ )
	{
		(*it)->dumpObject();
	}

	cout << "What file should be used for output? ";

	string sOutputFilename;
	cin >> sOutputFilename;


	ofstream output;
	output.open(sOutputFilename);

	outputXML(vWorld, output);

	output.close();

	return 0;
}
