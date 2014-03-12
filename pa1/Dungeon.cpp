#include <cmath>
#include <ncurses.h>
#include "Dungeon.h"
#include "Creature.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "GenericFactory.h"
#include "Tools.h"
using namespace std;

Dungeon::Dungeon()
{
	Tile tile(' ', false);
	vector<Tile> tiles;
	for (int i = 0; i < 79; i++)
		tiles.push_back(tile);

	for (int i = 0; i < 20; i++)
		m_vLevel.push_back(tiles);
}

vector<vector<Tile> > Dungeon::getLevel()
{
	return m_vLevel;
}

void Dungeon::findUpstairs(int &x, int &y)
{
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 79; j++)
		{
			if(m_vLevel[i][j].getSymbol() == '<')
			{
				x = j;
				y = i;
				return;
			}
		}
	}
}

void Dungeon::findDownstairs(int &x, int &y)
{
	for(int i = 0; i < 20; i++)
        {
                for(int j = 0; j < 79; j++)
                {
                        if(m_vLevel[i][j].getSymbol() == '>')
                        {
                                x = j;
                                y = i;
                                return;
                        }
                }
        }
}

void Dungeon::createLevel(mt19937 &mt)
{
	//Create the tunnels
	for(int i = 4; i < 16; i++)
	{
		for(int j = 14; j < 65; j++)
		{
			m_vLevel[i][15].setContent('#', true);
			m_vLevel[i][63].setContent('#', true);
			m_vLevel[4][j].setContent('#', true);
			m_vLevel[14][j].setContent('#', true);
		}
	}

	//Create the rooms
	for(int i = 0; i < 6; i++)
	{
		unsigned int iRandom = mt();
		int iRow;
		int iCol;
		if ( i % 2 == 0)
			iRow = (iRandom % 3) + 1;
		else
			iRow = (iRandom % 3) + 11;


		if ( i < 2 )
			iCol = (iRandom % 9) + 7;
		else if ( i < 4 )
			iCol = (iRandom % 9) + 28;
		else
			iCol = (iRandom % 9) + 49;

		if (iCol < 0 || iCol > 78 || iRow < 0 || iRow > 19)
		{
			cout << "out of range" << endl;
			return;
		}

		const int iMaxRow = iRow + (iRandom % 2) + 5;
		const int iMaxCol = iCol + (iRandom % 6) + 7;

		for (int j = iRow; j < iMaxRow; j++)
		{
			for (int k = iCol; k < iMaxCol; k++)
			{
				m_vLevel[j][k].setContent('.', true);
				
				if(m_vLevel[iMaxRow][k].getSymbol() != '#') 
					m_vLevel[iMaxRow][k].setContent('-',false);
				if(m_vLevel[iRow - 1][k].getSymbol() != '#')
					m_vLevel[iRow - 1][k].setContent('-', false);
			}

			if (m_vLevel[j][iMaxCol].getSymbol() != '#')
				m_vLevel[j][iMaxCol].setContent('|', false);
			if (m_vLevel[j][iCol - 1].getSymbol() != '#')
				m_vLevel[j][iCol - 1].setContent('|', false);
		}
	}

	//Create upstairs and downstairs
	bool bUpstairs = false;
	bool bDownstairs = false;
	while (!bUpstairs || !bDownstairs)
	{
		unsigned int iRandom = mt();

		int y1 = iRandom % 6 + 1;
		int x1 = iRandom % 11 + 7;
		int y2 = iRandom % 6 + 11;
		int x2 = iRandom % 11 + 49;

		if(!bUpstairs && m_vLevel[y1][x1].getSymbol() == '.')
		{
			m_vLevel[y1][x1].setSymbol('<');
			bUpstairs = true;
		}

		if(!bDownstairs && m_vLevel[y2][x2].getSymbol() == '.')
		{
			m_vLevel[y2][x2].setSymbol('>');
			bDownstairs = true;
		}
	}	
}
void Dungeon::generateItems()
{
	int iValidConsumables = 0;
	int iValidWeapons = 0;
	int iValidArmor = 0;
	
	while(iValidConsumables < 2 )
	{
		Consumable * pConsumable = GenericFactory::instance().generateConsumable();

		int iX = Tools::randomValue(79);
		int iY = Tools::randomValue(20);
		if(m_vLevel[iY][iX].getPassable())
		{
			pConsumable->setX(iX);
			pConsumable->setY(iY);
			m_vItems.push_back(pConsumable);
			iValidConsumables++;
		}
	}

	while(iValidWeapons < Tools::randomValue(2)+1)
	{
		Weapon * pWeapon = GenericFactory::instance().generateWeapon();

		int iX = Tools::randomValue(79);
		int iY = Tools::randomValue(20);
		if(m_vLevel[iY][iX].getPassable())
		{
			pWeapon->setX(iX);
			pWeapon->setY(iY);
			m_vItems.push_back(pWeapon);
			iValidWeapons++;
		}
	}

	while(iValidArmor < Tools::randomValue(2)+1)
	{
		Armor * pArmor = GenericFactory::instance().generateArmor();

		int iX = Tools::randomValue(79);
		int iY = Tools::randomValue(20);
		if(m_vLevel[iY][iX].getPassable())
		{
			pArmor->setX(iX);
			pArmor->setY(iY);
			m_vItems.push_back(pArmor);
			iValidArmor++;
		}
	}
}

void Dungeon::generateCreatures(int iLevel)
{
	
	int iValidCreatures = 0;
	
	while(iValidCreatures < iLevel*1.3 + 3)
	{
		Creature * pCritter = GenericFactory::instance().generateCreature(iLevel * 1.3 + 20);
		int iX = Tools::randomValue(79);
		int iY = Tools::randomValue(20);
		if(m_vLevel[iY][iX].getPassable())
		{
			pCritter->setX(iX);
			pCritter->setY(iY);
			pCritter->generateInventory();
			m_vCreatures.push_back(pCritter);
			iValidCreatures++;
		}
	}
}

void Dungeon::Reveal(vector<vector<Tile>> & level, char cSymbol, int iX, int iY)
{
	if (iX >= 79 || iX < 0 || iY >= 20 || iY < 0)
		return;
	if ((m_vLevel[iY][iX].getSymbol() != cSymbol && m_vLevel[iY][iX].getSymbol() != '<') || level[iY][iX].getRevealed())
	{
		level[iY][iX].setRevealed(true);
		return;
	}
	
	level[iY][iX].setRevealed(true);

	Reveal(level, cSymbol, iX+1, iY);
	Reveal(level, cSymbol, iX, iY+1);
	Reveal(level, cSymbol, iX-1, iY);
	Reveal(level, cSymbol, iX, iY-1);
}
void Dungeon::outputLevel(int iPlayerX, int iPlayerY)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 79; j++)
		{	
			double dist = sqrt(pow(iPlayerX - j, 2) + pow(iPlayerY - i, 2));
			if (dist < 8)
				m_vLevel[i][j].setRevealed(true);
		}
	}
	/*char cSymbol = m_vLevel[iPlayerY][iPlayerX].getSymbol();
	if (cSymbol == '<' || cSymbol == '>')
		cSymbol = '.';
	Reveal(m_vLevel, cSymbol, iPlayerX, iPlayerY);*/
			
	vector<vector<Tile> > vTemp = m_vLevel;
				
	for (auto it : m_vItems)
	{
		double dist = sqrt((iPlayerX - it->getX()) * (iPlayerX - it->getX()) + (iPlayerY - it->getY()) * (iPlayerY - it->getY()));
		if(dist < 8)
			vTemp[it->getY()][it->getX()].setSymbol(it->getSymbol());
	}

	for (auto it : m_vCreatures)
	{
		double dist = sqrt((iPlayerX - it->getX()) * (iPlayerX - it->getX()) + (iPlayerY - it->getY()) * (iPlayerY - it->getY()));
		if(dist < 8)
			vTemp[it->getY()][it->getX()].setSymbol(it->getSymbol());
	}

	vTemp[iPlayerY][iPlayerX].setSymbol('@');
	vector<vector<char>> vvChars;
	
	for (int i = 0; i < 20; i++)
	{
		vector<char> vChars;
		for (int j = 0; j < 79; j++)
		{
			if(vTemp[i][j].getRevealed())
				vChars.push_back(vTemp[i][j].getSymbol());
			else
				vChars.push_back(' ');
			//cout << vTemp[i][j].getSymbol();
		}
		vvChars.push_back(vChars);
		//cout << endl;
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j <79; j++)
		{
			//cout << vvChars[i][j];
			move(i,j);
			addch(vvChars[i][j]);
		}
		//cout << endl;
	}
}

void Dungeon::moveCreatures(int iPlayerX, int iPlayerY, Entity* player)
{
	for(auto it : m_vCreatures)
	{
		double dist = sqrt((iPlayerX - it->getX()) * (iPlayerX - it->getX()) + (iPlayerY - it->getY()) * (iPlayerY - it->getY()));
		if(dist < 7)
		{
			it->movePlayer(iPlayerX, iPlayerY, m_vLevel, player, getCreatures());
		}
	}
}

void Dungeon::addItem(Item* item)
{
	m_vItems.push_back(item);
}

Item * Dungeon::removeItem(int iX, int iY)
{
	Item* temp;
	vector<Item*> vTemp;
	for(auto it = m_vItems.begin(); it != m_vItems.end(); it++)
	{
		if((*it)->getX() == iX && (*it)->getY() == iY)
		{
			temp = *it;
			m_vItems.erase(it);	
			return temp;
		}
	}
	
	return NULL;

}

void Dungeon::outputItems()
{
	for(auto it : m_vItems)
	{
		it->dumpObject();
	}
}

vector<Entity*> Dungeon::getCreatures()
{
	return m_vCreatures;
}

bool Dungeon::checkCreatures()
{
	if(m_vCreatures.size() > 0)
	{	
		for(auto it = m_vCreatures.begin(); it != m_vCreatures.end(); it++)
		{
			Creature* creature = dynamic_cast<Creature*>(*it);	
			if(creature->getHealth() <= 0)
			{
				creature->drop(*this);	
				cout << "You Killed the " << (*it)->getName() << endl;
				m_vCreatures.erase(it);
				return true;
			}
		}
	}
	return false;
}
