#include "Fight.h"
#include "Globaldefs.h"
#include "Item.h"
#include "Loot.h"
#include "Actor.h"
#include "Hero.h"
#include "Mob.h"
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <ctime>

using namespace std;

void Fight::DrawTitle(class Actor* _Hero, class Actor* enemy)
{
	system("cls");
	cout << "Rozpoczela sie walka miedzy " << _Hero->GetName() << " a " << enemy->name << endl;
	cout << endl << "Wcisnij: 1. aby zaatakowac"/*, 2. aby uzyc umiejetnosci, 3. aby podejsc do przodu"*/ << endl;
}

bool Fight::MainFight(class Actor* _hero, class Actor* enemy)
{
	DrawTitle(_hero, enemy);
	while (_hero->GetHp() > 0 && enemy->GetHp() > 0)
	{
		switch (CheckFightAction())
		{
			case FIGHT_OPT::BASIC_ATTACK:
			{
				_hero->StandardAttack(enemy);
			}
		}
		Sleep(100);
		if (enemy->GetHp() > 0) enemy->StandardAttack(_hero);
		if (_hero->GetHp() <= 0) return false;

		cout << endl;
	}

	vector<class Item*> loots = CalculateLoot(_hero, enemy);
	cout << "LOOOTS" << loots.size() << endl;
	for (vector<class Item*>::iterator i = loots.begin(); i != loots.end(); i++)
	{
		cout << "Zdobyto " << (*i)->GetName() << endl;
		_hero->inventory += *i;
	}

	cout << endl << "Wygrana! Nacisnij dow. kl. aby wyjsc z walki";
	_getch();	
	system("cls");
	_hero->AddExperience(enemy->GetLevel() * 10);
	return true;
}

FIGHT_OPT Fight::CheckFightAction()
{
	FIGHT_OPT mv = WAITING;
	while (mv == WAITING)
	{
		switch (_getch())
		{
			case '1': mv = FIGHT_OPT::BASIC_ATTACK; break;
			default: mv = FIGHT_OPT::WAITING; break;
		}
	}

	return mv;
}

vector<class Item*> Fight::CalculateLoot(class Actor* & hero, class Actor * & enemy)
{
	int randomed_nr;
	vector<class Item*> result;
	for (vector<class Loot>::iterator i = enemy->possible_loots.begin(); i != enemy->possible_loots.end(); i++)
	{
		randomed_nr = rand() % 100;
		if (randomed_nr <= (*i).GetPercentage())
		{
			result.push_back((*i).GetLoot());
		}
	}

	return result;
}
