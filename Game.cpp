#include "Hero.h"
#include "Globaldefs.h"
#include "Item.h"
#include "Actor.h"
#include "NPC.h"
#include "Mob.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Game.h"
#include "Fight.h"
#include "Quest.h"
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

void Game::Lost()
{
	std::system("cls");
	Playing = false;
	Sleep(200);
	cout << "STRACILES CALE ZDROWIE! PRZEGRANA!";
	_getch();
}

void Game::InitializeMapManually()
{
	map = new class Map(80, 30, (char)219);
	map->AddObstacle(class Obstacle(70, 1));
	
	map->AddMob(new class Rat(10, 10));
	map->AddMob(new class Rat(20, 23));
	map->AddMob(new class Rat(20, 20));
	map->AddMob(new class Rat(20, 21));
	map->AddMob(new class Rat(20, 22));
	map->AddMob(new class Rat(19, 22));
	map->AddMob(new class Rat(18, 22));
	map->AddMob(new class Rat(19, 25));
	map->AddMob(new class Rat(17, 17));
	map->AddMob(new class Rat(26, 27));
	map->AddMob(new class Orc(20, 24));
	map->AddMob(new class Orc(21, 24));
	map->AddMob(new class Orc(21, 24));
	map->AddMob(new class Orc(21, 25));
	map->AddMob(new class Orc(22, 26));
	map->AddMob(new class Orc(22, 24));
	map->AddMob(new class Orc(23, 24));
	map->AddMob(new class Orc(24, 24));
	map->AddMob(new class Orc(25, 24));
	map->AddMob(new class Orc(26, 24));
	map->AddNPC(new class Villager(71, 10));
	map->AddNPC(new class Chest(78, 2, 0, "Skrzynia", (char)219));
}

void Game::InitializeHeroManually()
{
	hero = new class Hero(50, 22, 1);
	hero->AddQuest(new class KillRats);
}

bool Game::InitializeHeroInventoryManually()
{
	if (hero != NULL)
	{
		hero->AddToInventory(new class Meat, 2);
		hero->AddToInventory(new class ManaMixture, 2);
		hero->AddToInventory(new class GoldRing, 2);
		hero->AddToInventory(new class LeatherArmor);
		hero->AddToInventory(new class LeatherArmor);
		hero->AddToInventory(new class LeatherHelmet);
		hero->AddToInventory(new class LeatherShoes);
		hero->AddToInventory(new class Sword);
		hero->AddToInventory(new class SimpleShield, 5);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::MainGame()
{
	if (map_need_to_be_refreshed == true)
	{
		system("cls");
		map->DrawBorder(); 
		map->DrawInside();
	}
	
	hero->DrawHpManaBar(map->GetHeight());
	hero->Clr();
	hero->CheckMove(*map);
	hero->Draw();

	switch (hero->CheckAction())
	{
		int number;
		case ATTACK:
		{
			vector<class Mob*> mobs = map->GetMobVector();
			vector<class Mob*>::iterator it = hero->TryAttack(mobs, number);
			class Actor* _hero = hero;
			class Actor* _mob = *it;
			if (it != mobs.end())
			{
				if (!FIGHT.MainFight(hero, mobs.at(number)))
					Lost();
				try
				{
					hero->AddKilledMobToMissions(mobs.at(number));
					class Mob* del = mobs.at(number);
					(*del).Clr();
				}
				catch (out_of_range)
				{
					cout << number << "  BLAD KRYTYCZNY, NUMER POTWORA POZA VECTOREM";
				}

				map_need_to_be_refreshed = true;
			}
			break;
		}
		case TALK:
		{
			auto NPCs = map->GetNPCVector();
			auto it = hero->TryTalk(NPCs, number);
			if (it != NPCs.end())
			{
				(*NPCs.at(number)).Talk();
				map_need_to_be_refreshed = true;
			}
			break;
		}
		case OPEN_INVENTORY:
		{
			hero->inventory.ShowInventory(hero);
			map_need_to_be_refreshed = true;
			break;
		}
		case OPEN_EQ:
		{
			hero->inventory.equipment.ShowEquipment();
			map_need_to_be_refreshed = true;
			break;
		}
		case OPEN_STATS:
		{
			hero->ShowHeroStats();
			map_need_to_be_refreshed = true;
			break;
		}
		case OPEN_DIARY:
		{
			hero->ShowDiary();
			map_need_to_be_refreshed = true;
			break;
		}
		default:
		{
			map_need_to_be_refreshed = false;
			break;
		}		
	}
	Sleep(100);
}

Game::Game()
{
	srand(time(NULL));
	ChangeColor(15);
	HideCursor();
	this->Playing = true;
	InitializeMapManually();
	InitializeHeroManually();
	InitializeHeroInventoryManually();
	_SMALL_RECT win;
	win.Top = 200;
	win.Left = 200;
	win.Bottom = 400;
	win.Right = 400;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &win);

	map_need_to_be_refreshed = false;
	map->DrawBorder();
	map->DrawInside();
}