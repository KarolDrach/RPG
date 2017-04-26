#include "Hero.h"
#include "Globaldefs.h"
#include "Item.h"
#include "NPC.h"
#include "Mob.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Game.h"
#include "Fight.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

void main()
{
	/*LevelCaps caps;
	caps.InitLevelCaps();*/

	Game GAME;

	while (GAME.GetPlaying())
	{		
		GAME.MainGame();
	}

	std::system("pause");
}