#pragma once
#include "Globaldefs.h"

using namespace std;

class Fight
{
public:
	void DrawTitle(class Actor* _Hero, class Actor* enemy);
	bool MainFight(class Actor* _hero, class Actor* enemy);
	FIGHT_OPT CheckFightAction();
	vector<class Item*> CalculateLoot(class Actor* & hero, class Actor* & enemy);
};