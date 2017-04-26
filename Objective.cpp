#include "stdafx.h"
#include "Objective.h"
#include "Mob.h"
#include <stdarg.h>

using namespace std;

void KillMonster::ShowStatus()
{
	cout << monster->GetName() << ", pozostalo: " << actual_amount << "/" << amount_to_kill << endl;
}

void KillMonster::IncAmount()
{
	if ((this->actual_amount + 1) <= amount_to_kill)
		this->actual_amount++;	

	if (CheckIfConditionFilled())
		this->condition_fullfilled = true;
}

bool KillMonster::CheckIfConditionFilled()
{
	if (this->actual_amount >= this->amount_to_kill)
		return true;
	else
		return false;
}

KillMonster::KillMonster(int amount_to_kill, Mob * monster)
{
	this->amount_to_kill = amount_to_kill;
	this->monster = monster;
}

KillMonstersWhole::KillMonstersWhole(int amount, KillMonster first, ...)
{
	conditions_fullfilled = false;
	id = KILLWHOLEMONSTERS;

	va_list arguments;
	va_start(arguments, first);
	int auxiliary_iterator = 1;

	for (KillMonster i = first; auxiliary_iterator <= amount; )
	{
		this->vector_of_monsters_to_kill.push_back(i);
		auxiliary_iterator++;
		if (!(auxiliary_iterator > amount))
			i = va_arg(arguments, KillMonster);
	}
	va_end(arguments);
}

void KillMonstersWhole::ShowObjectiveStatus()
{
	for (vector<KillMonster>::iterator i = vector_of_monsters_to_kill.begin(); i != vector_of_monsters_to_kill.end(); i++)
		(*i).ShowStatus();

	cout << " EEE    " << this->GetConditionsState();
}

void KillMonstersWhole::CheckIfConditionsFilled()
{
	bool all = true;
	for (vector<KillMonster>::iterator i = vector_of_monsters_to_kill.begin(); i != vector_of_monsters_to_kill.end(); i++)
		if (!(*i).CheckIfConditionFilled())
		{
			all = false;
		}

	if (all)
		this->conditions_fullfilled = true;
}

void ReachXY::ShowObjectiveStatus()
{
	cout << this->status_text;
}

void ReachXY::CheckIfConditionsFilled()
{
	if (this->x == x && this->y == y)
		this->conditions_fullfilled = true;
}

ReachXY::ReachXY(int x, int y, string status_text)
{
	conditions_fullfilled = false;
	id = REACHXY;

	this->conditions_fullfilled = true;
	this->x = x;
	this->y = y;
	this->status_text = status_text;
}
