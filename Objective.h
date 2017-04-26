#pragma once
#include <vector>
#include "Globaldefs.h"

extern class Mob;

using namespace std;

class KillMonster;

class Objective
{
protected:
	bool conditions_fullfilled;
	OBJECTIVE_ID id;
public:
	Objective() {}
	bool GetConditionsState() { return conditions_fullfilled; }
	virtual void ShowObjectiveStatus() = 0;
	virtual void CheckIfConditionsFilled() = 0;
	virtual vector<KillMonster> GetMonstersToKill() = 0;
	virtual vector<KillMonster>::iterator GetBeginOfMonstersToKill() = 0;
	virtual vector<KillMonster>::iterator GetEndOfMonstersToKill() = 0;
	virtual OBJECTIVE_ID GetID() { return id; }
	virtual ~Objective() {}
};

class KillMonster
{
	int amount_to_kill;
	int actual_amount;
	Mob* monster;
	bool condition_fullfilled;
public:
	void ShowStatus();
	void IncAmount();
	bool CheckIfConditionFilled();
	Mob* GetMob() { return monster; }
	KillMonster(int amount_to_kill, Mob* monster);
};

class KillMonstersWhole : public Objective
{
	vector<KillMonster> vector_of_monsters_to_kill;
public:
	virtual void ShowObjectiveStatus();
	virtual void CheckIfConditionsFilled();
	virtual vector<KillMonster> GetMonstersToKill() { return vector_of_monsters_to_kill; }
	virtual vector<KillMonster>::iterator GetBeginOfMonstersToKill() { return vector_of_monsters_to_kill.begin(); }
	virtual vector<KillMonster>::iterator GetEndOfMonstersToKill() { return vector_of_monsters_to_kill.end(); }
	KillMonstersWhole(int amount, KillMonster first, ...);
};

class ReachXY : public Objective
{
	int x, y;
	string status_text;
	vector<KillMonster> test;
public:
	virtual vector<KillMonster> GetMonstersToKill() { return test; }
	virtual vector<KillMonster>::iterator GetBeginOfMonstersToKill() { return test.begin(); }
	virtual vector<KillMonster>::iterator GetEndOfMonstersToKill() { return test.end(); }
	virtual void ShowObjectiveStatus();
	virtual void CheckIfConditionsFilled();
	ReachXY(int x, int y, string status_text);
};

