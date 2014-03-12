
#include "GenericFactory.h"

using namespace std;

int main(int argc, char * argv[])
{
	for( int i = 0; i < 3; i++ )
	{
		Creature * pCritter = GenericFactory::instance().generateCreature(20);
		pCritter->dumpObject();
		cout << endl;

		delete pCritter;

		
		Item * pItem = GenericFactory::instance().generateItem();

		pItem->dumpObject();
		cout << endl;

		delete pItem;
	}

	return 0;
}


