#include "Tools.h"

#include <random>
#include <sstream>

using namespace std;

int Tools::randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}


