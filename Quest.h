#pragma once
#include "Globaldefs.h"
#include <vector>

extern class Objective;

using namespace std;

class Quest
{
protected:
	string name;
	vector<Objective*> objectives_list;
	vector<Objective*>::iterator quest_state;
public:
	Quest() {}
	vector<Objective*>::iterator GetQuestState() { return quest_state; }
	OBJECTIVE_ID GetQuestStateID();
	vector<Objective*> GetObjectivesList() { return objectives_list; }
	virtual void CheckRaiseQuestState();
	virtual void ShowDescription() = 0;
	virtual ~Quest() {}
};

class KillRats : public Quest
{
public:
	virtual void ShowDescription();
	KillRats();
};

