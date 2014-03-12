#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <functional>
#include <map>
#include <cstdlib>
#include <vector>
#include <csignal>
#include <ctime>
#include <random>
#include <sstream>
#include <istream>
#include <ncurses.h>

#include "Armor.h"
#include "Creature.h"
#include "Weapon.h"
#include "Item.h"
#include "XMLSerializable.h"
#include "Dungeon.h"
#include "GenericFactory.h"
#include "Tools.h"
#include "EntityVector.h"
#include "parser.h"
#include "Player.h"

using namespace std;

void outputXML(vector<XMLSerializable*> vObjects)
{	
	ofstream output;
	//string sOutputFile;
	//cout << "What should we name the new XML file? ";
	//cin >> sOutputFile;
	string sOutputFile = "save.xml";
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
}

template< typename T >
inline T convert(const string& str)
{
    istringstream iss(str);
    T obj;

    iss >> ws >> obj >> ws;

    if(!iss.eof())
        throw "dammit!";
    else if(str.length() == 0)
 	throw "invalid";

    return obj; 
}

int main(int argc, char * argv[])
{
	vector<Dungeon> vDungeon;
	mt19937 mt;
	mt.seed( time(NULL));
	for (int i = 0; i < 25; i++)
	{
		Dungeon dLevel;
		dLevel.createLevel(mt);
		dLevel.generateItems();
		dLevel.generateCreatures(i);
		vDungeon.push_back(dLevel);
	}
	cout << "Use the w, a, s, and d keys to move. Use p to pick up items and o to drop them. q to quit.\n";
	cout << "Use < to go upstairs and > to go downstairs. Use e to equip items and u to use consumables.\n";
	cout << "For extra credit I added a more robust inventory with error checking on inputs. I also made it handle non hostile mosters properly so they will not attack unless attacked first.\n I also make it so that the dungeon is hidden until you come within so many tiles of it. This reveals the tiles forever but if you move away from mosters or items they become hidden once again.\n\n";
	cout << "Press ENTER to continue\n";
	cin.ignore(200, '\n');
	int iUpX; int iUpY;
	int iDownX; int iDownY;
	vDungeon[0].findUpstairs(iUpX, iUpY);
	Player player;
	player.setCoords(iUpX, iUpY);
	bool bWon = false;
	bool bLost = false;
	bool bLeft = false;
	bool bQuit = false;
	int iInput;
	int iCurrentLevel = 0;
	bool bHealthChange1 = false;
	bool bHealthChange2 = false;
	bool bHealthChange3 = false;
	int iTurnCounter = 0;
	stringstream ssOutputBasic;
	stringstream ssOutput;
	initscr();
	while(!bWon && !bLost && !bQuit && !bLeft)
	{
		refresh();
		clear();
		ssOutputBasic.str("");
		vDungeon[iCurrentLevel].outputLevel(player.getX(), player.getY());
		ssOutputBasic << "Level: " << player.getLevel() << " Health: " << player.getHealth() << endl;
		move(19, 0);
		addstr(ssOutputBasic.str().c_str());
		move(20,0);
		addstr(ssOutput.str().c_str());
		ssOutput.str("");
		iInput = getch();
		string sConf;
		int iHealth = player.getHealth();
		move(20,0);
		if(iInput == 'q')
		{
			addstr("Are you sure you want to quit? [y/n] ");
			if(getch() == 'y')
				bQuit = true;
		}

		else if(iInput == 'w' || iInput == 'a' || iInput == 's' || iInput == 'd')
		{
			player.movePlayer(iInput, vDungeon[iCurrentLevel], ssOutput);
			vDungeon[iCurrentLevel].moveCreatures(player.getX(), player.getY(), dynamic_cast<Entity*>(&player));	
		}

		else if(iInput == 'p')
		{
			player.pickUp(vDungeon[iCurrentLevel]);
		}

		else if(iInput == 'i')
		{
			player.displayInventory();
			addstr("Press any key to exit inventory.");
			getch();
		}

		/*else if(iInput == 'items')
		{
			vDungeon[iCurrentLevel].outputItems();
		}*/

		else if(iInput == 'o')
		{
			if(player.getInvSize() == 0)
				ssOutput << "You have nothing to drop.";
			else
			{
				int iDrop = -1;
				do
				{
					iDrop = -1;
					string sDrop;
					move(20,0);
					clrtoeol();
					ssOutput.str("");
					ssOutput << "Which Item to drop? (1-" << player.getInvSize() << ") ";
					addstr(ssOutput.str().c_str());
					ssOutput.str("");
					char cStr[] = "";
					try { getstr(cStr); }
					catch(int e) { addstr("WTF?"); }
					sDrop = cStr;
					try
					{
						iDrop = convert<int>(sDrop);

					}
					catch(char const* e)
					{
						move(20,0);
						clrtoeol();
						addstr("Please enter a valid number. ");
					}
				} while (iDrop < 0 || iDrop > player.getInvSize());
				player.drop(iDrop-1, vDungeon[iCurrentLevel]);
			}
		}
		
		else if(iInput == 'e')
		{
			int iEquip = -1;
			do
			{
				iEquip = -1;
				string sEquip;
				move(20,0);
				clrtoeol();
				ssOutput.str("");
				ssOutput << "Which Item to equip? (1-" << player.getInvSize() << ") ";
				addstr(ssOutput.str().c_str());
				ssOutput.str("");
				char cStr[] = "";
				getstr(cStr);
				sEquip = cStr;
				try
				{
					iEquip = convert<int>(sEquip);
				}
				catch(char const* e)
				{
					move(20,0);
					clrtoeol();
					addstr("Please enter a valid number. ");
				}
			} while (iEquip < 0 || iEquip > player.getInvSize());
			player.equip(iEquip, ssOutput);
		}
		
		else if(iInput == 'u')
		{
			int iUse = -1;
			do
			{
				iUse = -1;
				move(20,0);
				clrtoeol();
				ssOutput.str("");
				char cStr[] = "";
				ssOutput << "Which Consumable to use? (1-" << player.getInvSize() << ") ";
				addstr(ssOutput.str().c_str());
				ssOutput.str("");
				getstr(cStr);
				string sUse = cStr;
				
				try
				{
					iUse = convert<int>(sUse);
				}
				catch(char const* e)
				{
					move(20,0);
					clrtoeol();
					addstr("Please enter a valid number. ");
				}
			} while(iUse <= 0 || iUse > player.getInvSize());
			iUse--;
			if(dynamic_cast<Consumable*>(player.getInventory()[iUse]) != NULL )
				dynamic_cast<Consumable*>(player.getInventory()[iUse])->use(player, iUse);
			else
				addstr("You can only use consumables.");
		}

		else if(iInput == '>')
		{
			vDungeon[iCurrentLevel].findDownstairs(iDownX, iDownY);
			if(player.getX() == iDownX && player.getY() == iDownY)
			{
				iCurrentLevel++;
				if(iCurrentLevel == 25)
				{
					bWon = true;
				}
				else
				{	
					vDungeon[iCurrentLevel].findUpstairs(iUpX, iUpY);
					player.setCoords(iUpX, iUpY);
				}
			}
			else
				addstr("This command can only be used over downstairs ('>')");
		}

		else if(iInput == '<')
		{
			vDungeon[iCurrentLevel].findUpstairs(iUpX, iUpY);
			if(player.getX() == iUpX && player.getY() == iUpY)
			{
				iCurrentLevel--;
				if(iCurrentLevel == -1)
				{
					bLeft = true;
				}
				else
				{
					vDungeon[iCurrentLevel].findDownstairs(iDownX, iDownY);
					player.setCoords(iDownX, iDownY);
				}
			}
			else
				addstr("This command can only be used over upstairs ('<')");
		}

		/*else if(iInput == "dropit")
		{
			for (auto it : vDungeon[iCurrentLevel].getCreatures())
			{
				Creature* pCreature = dynamic_cast<Creature*>(it);
				pCreature->drop(vDungeon[iCurrentLevel]);
			}
		}*/
		if(player.getHealth() <= 0)
			bLost = true;
		bHealthChange3 = bHealthChange2;
		bHealthChange2 = bHealthChange1;
		iTurnCounter++;
		if(player.getHealth() == iHealth)
			bHealthChange1 = true;
		else
			bHealthChange1 = false;
		if(player.getHealth() < player.getMaxHealth() && bHealthChange1 && bHealthChange2 && bHealthChange3 && iTurnCounter % 3 == 0)
			player.setHealth(player.getHealth()+1);
		bool bKill = false;
		if(iCurrentLevel >= 0)
			bKill = vDungeon[iCurrentLevel].checkCreatures();
		if(bKill)
			player.setExperience(player.getExperience() + 50);
		if(player.getExperience() >= player.getExperienceNeeded())
			player.levelUp();
		Creature critter;
		cout << critter.getHealth() << endl;
	}
	endwin();
	if(bLost)
	{
		cout << "You have died. Better luck next time." << endl;
	}

	if(bLeft)
	{
		cout << "You have left the dungeon." << endl;
	}

	if(bWon)
	{
		cout << "Congrats! You have finished the dungeon." << endl;
	}
	
	cout << "Your score is " << player.getExperience() << endl;
		
	return 0;
}
