#ifndef _DungeonLevel_included_
#define _DungeonLevel_included_

#include <vector>
#include <random>

class DungeonLevel
{
public:
	DungeonLevel(int iWidth, int iHeight, std::mt19937 & mt);
	~DungeonLevel(void);

	void dump();
	char at(int x, int y);

	int getWidth();
	int getHeight();

private:
	std::vector<std::vector<char>> m_vvTiles;

};

#endif