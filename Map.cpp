#include "Map.h"
#include "Globaldefs.h"
#include "Mob.h"
#include "NPC.h"
#include <vector>
#include <Windows.h>

using namespace std;

/* FUNCTION ONLY FOR TESTING, HAS NO USE IN REAL PROGRAM*/
void Map::DrawAllMobsHP()
{
	gotoxy(0, 45);
	for (vector<class Mob*>::iterator i = monsters.begin(); i != monsters.end(); i++)
	{
		cout << (*i)->name << " " << (*i)->GetHp() << " " << *i << "    " << endl;
	}
}

void Map::AddObstacle(class Obstacle obstacle)
{
	this->obstacles.push_back(obstacle);
}

void Map::AddNPC(class NPC * npc)
{
	this->NPCs.push_back(npc);
}

void Map::AddMob(class Mob * mob)
{
	this->monsters.push_back(mob);
}

/* NOT STABLE FUNCS DONT USE*/
void Map::DeleteObstacle(vector<class Obstacle>::iterator iterator)
{
	this->obstacles.erase(iterator);
}

void Map::DeleteMob(vector<class Mob*>::iterator iterator)
{
	monsters.erase(iterator);
}

void Map::DeleteNPC(vector<class NPC*>::iterator iterator)
{
	this->NPCs.erase(iterator);
}
/* NOT STABLE FUNCS DONT USE*/

void Map::DrawBorder()
{
	ChangeColor(15);
	gotoxy(0, 0);
	char symb = this->border_symbol;
	for (int i = 1; i <= this->height; i++)
	{
		if (i == 1 || i == this->height)
		{
			for (int j = 1; j <= this->width; j++)
				//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symb, 1, 0, 0);
				cout << symb;
		}
		else
		{
			//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symb, 1, 0, 0);
			cout << symb;
			gotoxy(this->width - 1, i - 1);
			//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symb, 1, 0, 0);
			cout << symb;
		}

		cout << endl;
	}
}

void Map::DrawInside()
{
	/* temporary solution for deleting mobs with 0 hp*/
	if (!monsters.empty())
	{
		for (vector<class Mob*>::iterator i = monsters.begin(); i != monsters.end(); )
		{
			if ((*i)->GetHp() <= 0)
			{
				i = monsters.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
	/* temporary solution for deleting mobs with 0 hp*/
	
	if (!monsters.empty())
	{
		ChangeColor(4);   // KOLOR CZERWONY
		for (vector<class Mob*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		{
			gotoxy((*i)->pos_x, (*i)->pos_y);
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &((*i)->map_symbol), 1, 0, 0);
		}
		ChangeColor(15);  //POWROT DO KOLORU JASK. BIALEGO
	}

	if (!NPCs.empty())
	{
		for (vector<class NPC*>::iterator i = NPCs.begin(); i != NPCs.end(); i++)
		{
			ChangeColor((*i)->color);
			gotoxy((*i)->pos_x, (*i)->pos_y);
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &((*i)->map_symbol), 1, 0, 0);
		}
		ChangeColor(15);  // JASK. BIALY
	}

	if (!obstacles.empty())
	{
		for (vector<class Obstacle>::iterator i = obstacles.begin(); i != obstacles.end(); i++)
		{
			ChangeColor((*i).color);
			gotoxy((*i).pos_x, (*i).pos_y);
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &((*i).map_symbol), 1, 0, 0);
		}
	}
	
	ChangeColor(15);
}

Map::Map(int width, int height, char border_symbol)
{
	this->width = width;
	this->height = height;
	this->border_symbol = border_symbol;
}

/**** TO TESTING/
/*
gotoxy(2, 2);
cout << (*it)->GetHp();
gotoxy(0, 40);
for (vector<Mob*>::iterator i = mobs.begin(); i != mobs.end(); i++)
cout << (*i)->GetName() << " " << (*i)->GetHp() << " " << *i <<"    "  << endl;
test_map.DrawAllMobsHP();
//test_map.DeleteMob(it);
mobs.erase(it);
gotoxy(0, 55);
for (vector<Mob*>::iterator i = mobs.begin(); i != mobs.end(); i++)
cout << (*i)->GetName() << " " << (*i)->GetHp() << " " << *i << "    " << endl;
test_map.DrawAllMobsHP();
test_map.monsters.erase(it);
*/