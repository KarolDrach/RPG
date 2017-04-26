#include "stdafx.h"
#include "Quest.h"
#include "Objective.h"
#include "Mob.h"

using namespace std;

void KillRats::ShowDescription()
{
	ChangeColor(14);
	cout << name << endl << endl;
	ChangeColor(15);
	(*quest_state)->ShowObjectiveStatus();	
}

KillRats::KillRats()
{
	this->name = "Zabij kilka szczurow dla straznika";
	this->quest_state = objectives_list.begin();
	objectives_list.push_back(new class KillMonstersWhole(2,
													class KillMonster(5, new class Rat),
													class KillMonster(2, new class Orc)));
	objectives_list.push_back(new class KillMonstersWhole(1,
													class KillMonster(3, new class Rat)));

	objectives_list.push_back(new class ReachXY(10, 15, "Udaj sie gdziestam"));
	quest_state = objectives_list.begin();
}

OBJECTIVE_ID Quest::GetQuestStateID()
{
	return (*quest_state)->GetID();
}

void Quest::CheckRaiseQuestState()
{
	vector<class Objective*>::iterator buffer = quest_state;
	(*quest_state)->CheckIfConditionsFilled();
	if ((*quest_state)->GetConditionsState() && ++buffer != this->objectives_list.end())
		quest_state++;
}
