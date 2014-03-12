#include <iostream>
#include "Item.h"

using namespace std;

int main(int argc, char * argv[])
{
	Item item;
	item.setName("Wombat");
	cout << "The item is a " << item.getName() << endl;

	return 0;
}
