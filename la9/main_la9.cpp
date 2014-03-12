
#include "CreatureFactory.h"

using namespace std;

int main(int argc, char * argv[])
{
	for (int i = 0; i<5; i++)
	{
		Creature * pCritter = CreatureFactory::instance().generateCreature(30);
		pCritter->dumpObject();

		delete pCritter;
	}

	return 0;
}


