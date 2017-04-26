#include "Hero.h"
#include "NPC.h"
#include "Mob.h"
#include "Bonus.h"
#include "Inventory.h"
#include "Item.h"
#include "Map.h"
#include "Quest.h"
#include "Objective.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

Hero::Hero(int pos_x, int pos_y, int level, string name)
{
	actor_id = PLAYER;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->level = level;
	this->basic_max_hp = 50 + level*10 + 2000;	
	this->basic_max_mana = 10 + level*2 + 2000;	
	this->name = name;
	DIR = UP;
	hp = basic_max_hp;
	mana = basic_max_mana;
	basic_attack_damage = 10 + level * 2;// +2000;
	basic_defence = 5 + level;
	basic_critical_hit_chance = 2 + level + 150;

	// INIT WHOLE STATS, AT THAT MOMENT THEY ARE EQUAL TO BASIC(WITHOUT ITEMS BONUSES) STATS//
	whole_max_mana = basic_max_mana;
	whole_max_hp = basic_max_hp;
	whole_strength = basic_strength;
	whole_attack_damage = basic_attack_damage;
	whole_defence = basic_defence;
	whole_critical_hit_chance = basic_critical_hit_chance;
	this->actual_experience = 0;
	this->next_level_experience = CalculateNewLevelExp(level);
}

void Hero::Draw()
{
	gotoxy(pos_x, pos_y);
	char symbol;
	switch (DIR)
	{
	case UP: symbol = '^'; break;
	case DOWN: symbol = 'v'; break;
	case LEFT: symbol = '<'; break;
	case RIGHT: symbol = '>'; break;
	}

	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symbol, 1, 0, 0);
}

void Hero::DrawHpManaBar(int map_height)
{
	gotoxy(0, map_height + 1);
	cout << this->GetName() << "(" << this->GetLevel() << ")";

	gotoxy(0, map_height + 3);
	int i = 1;
	ChangeColor(12);
	for (i; i <= ((float)this->GetHp() / (float)this->GetMaxHp() * 100.0) / 2; i++)
	{
		cout << (char)219;
	}

	for (i; i <= 50; i++)
		cout << " ";

	ChangeColor(7);
	cout << "     Zdrowie:       " << (int)(((float)this->GetHp() / (float)this->GetMaxHp()) * 100.0) << "%" << " "<< this->GetHp() << "/" << this->GetMaxHp();

	gotoxy(0, map_height + 4);
	ChangeColor(1);
	for (i = 1; i <= ((float)this->GetMana() / (float)this->GetMaxMana() * 100.0) / 2; i++)
	{
		cout << (char)219;
	}

	for (i; i <= 50; i++)
		cout << " ";
	ChangeColor(7);
	cout << "     Mana:          " << (int)(((float)this->GetMana() / (float)this->GetMaxMana()) * 100.0) << "%" << " " << this->GetMana() << "/" << this->GetMaxMana();

	gotoxy(0, map_height + 5);
	ChangeColor(6);
	for (i = 1; i <= ((float)this->GetActualExperience() / (float)this->GetNextLevelExperience() * 100.0) / 2; i++)
	{
		cout << (char)219;
	}

	for (i; i <= 50; i++)
		cout << " ";
	ChangeColor(7);
	cout << "     Doswiadczenie: " << (int)(((float)this->GetActualExperience() / (float)this->GetNextLevelExperience()) * 100.0) << "%" << " " << this->GetActualExperience() << "/" << this->GetNextLevelExperience();
}

void Hero::CheckMove(class Map & map)
{
	int next_y = pos_y, next_x = pos_x;
	bool collision_flag = false;

	if (GetAsyncKeyState(VK_UP))
	{
		if (DIR == UP)
			next_y--;
		else
			this->DIR = UP;
	}
	else
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (DIR == DOWN)
				next_y++;
			else
				this->DIR = DOWN;
		}
		else
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (DIR == LEFT)
				next_x--;
			else
				this->DIR = LEFT;
		}
		else
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (DIR == RIGHT)
				next_x++;
			else
				this->DIR = RIGHT;
		}

	if (next_x == 0 || next_x == (map.width - 1) || next_y == 0 || next_y == (map.height - 1))
		collision_flag = true;

	if (!map.monsters.empty() && !collision_flag)
	{
		for (vector<class Mob*>::iterator i = map.monsters.begin(); i != map.monsters.end(); i++)
		{
			if ((*i)->pos_x == next_x && (*i)->pos_y == next_y)
			{
				collision_flag = true;
				break;
			}
		}
	}

	if (!map.NPCs.empty() && !collision_flag)
	{
		for (vector<class NPC*>::iterator i = map.NPCs.begin(); i != map.NPCs.end(); i++)
		{
			if ((*i)->pos_x == next_x && (*i)->pos_y == next_y)
			{
				collision_flag = true;
				break;
			}
		}
	}

	if (!map.obstacles.empty() && !collision_flag)
	{
		for (vector<class Obstacle>::iterator i = map.obstacles.begin(); i != map.obstacles.end(); i++)
		{
			if ((*i).pos_x == next_x && (*i).pos_y == next_y)
			{
				collision_flag = true;
				break;
			}
		}
	}

	if (!collision_flag)
	{
		pos_x = next_x;
		pos_y = next_y;
	}
}

void Hero::RecalculateHeroStatsWithItems()
{
	int additional_hp = 0;
	int additional_mana = 0;
	int additional_strength = 0;
	int additional_dexterity = 0;
	int additional_intelligence = 0;
	int additional_attack_damage = 0;
	int additional_defence = 0;
	int additional_critical_hit_chance = 0;
	int additional_piercing_hit_chance = 0;
	whole_max_hp = basic_max_hp;
	whole_max_mana = basic_max_mana;
	whole_strength = basic_strength;
	whole_dexterity = basic_dexterity;
	whole_intelligence = basic_intelligence;
	whole_attack_damage = basic_attack_damage;
	whole_defence = basic_defence;
	whole_critical_hit_chance = basic_critical_hit_chance;
	whole_piercing_hit_chance = basic_piercing_hit_chance;
	
	vector<class Item*> tmp_items_vector = inventory.GetEquipmentAsVector();
	for (vector<class Item*>::iterator i = tmp_items_vector.begin(); i != tmp_items_vector.end(); i++)
	{
		vector<class Bonus<>> vect = (*i)->GetBonusesVector();
		for (vector<class Bonus<>>::iterator j = vect.begin(); j != vect.end(); j++)
		{
			switch ((*j).GetType())
			{
				case ADD_STRENGTH:
				{
					additional_strength += (*j).GetValueOfType();
					break;
				}
				case ADD_DEXTERITY:
				{
					additional_dexterity += (*j).GetValueOfType();
					break;
				}
				case ADD_INTELLIGENCE:
				{
					additional_intelligence += (*j).GetValueOfType();
					break;
				}
				case ADD_MAX_MANA:
				{
					additional_mana += (*j).GetValueOfType();
					break;
				}
				case ADD_MAX_HP:
				{
					additional_hp += (*j).GetValueOfType();
					break;
				}
				case ADD_ATTACK_DAMAGE:
				{
					additional_attack_damage += (*j).GetValueOfType();
					break;
				}
				case ADD_DEFENCE:
				{
					additional_defence += (*j).GetValueOfType();
					break;
				}
				case ADD_CRITICAL_HIT_CHANCE:
				{
					additional_critical_hit_chance += (*j).GetValueOfType();
				}
				case ADD_PIERCING_HIT_CHANCE:
				{
					additional_piercing_hit_chance += (*j).GetValueOfType();
				}
			}
		}
	}
	
	whole_max_hp += additional_hp;
	whole_max_mana += additional_mana;
	whole_strength += additional_strength;
	whole_dexterity += additional_dexterity;
	whole_intelligence += additional_intelligence;
	whole_attack_damage += additional_attack_damage;
	whole_defence += additional_defence;
	whole_critical_hit_chance += additional_critical_hit_chance;
	whole_piercing_hit_chance += additional_piercing_hit_chance;
}

void Hero::ShowHeroStats()
{
	system("cls");
	ChangeColor(10);
	cout << "Max hp.: " << whole_max_hp;
	ChangeColor(14);
	cout << "(" << basic_max_hp << ")" << endl;
	
	ChangeColor(10);
	cout << "Max mana: " << whole_max_mana;
	ChangeColor(14);
	cout << "(" << basic_max_mana << ")" << endl;
	
	ChangeColor(10);
	cout << "Sila: " << whole_strength;
	ChangeColor(14);
	cout << "(" << basic_strength << ")" << endl;

	ChangeColor(10);
	cout << "Zrecznosc: " << whole_dexterity;
	ChangeColor(14);
	cout << "(" << basic_dexterity << ")" << endl;

	ChangeColor(10);
	cout << "Intelekt: " << whole_intelligence;
	ChangeColor(14);
	cout << "(" << basic_intelligence << ")" << endl;
	
	ChangeColor(10);
	cout << "Atak: " << whole_attack_damage;
	ChangeColor(14);
	cout << "(" << basic_attack_damage << ")" << endl;
	
	ChangeColor(10);
	cout << "Obrona: " << whole_defence;
	ChangeColor(14);
	cout << "(" << basic_defence << ")" << endl;
	
	ChangeColor(10);
	cout << "Cios krytyczny: " << whole_critical_hit_chance;
	ChangeColor(14);
	cout << "(" << basic_critical_hit_chance << ")" << endl;

	ChangeColor(10);
	cout << "Przebicie pancerza: " << whole_piercing_hit_chance;
	ChangeColor(14);
	cout << "(" << basic_piercing_hit_chance << ")" << endl;

	ChangeColor(15);
	cout << "Dow. klawisz aby zamknac";
	_getch();
}

void Hero::ShowDiary()
{
	system("cls");
	if (!quests.empty())
	{
		for (vector<class Quest*>::iterator i = quests.begin(); i != quests.end(); i++)
		{
			(*i)->ShowDescription();
		}
	}
	
	cout << endl << endl << "Nacisnij dow. klawisz, aby zamknac";
	_getch();
}

void Hero::AddKilledMobToMissions(class Mob* mob)
{
	if (!quests.empty())
	{
		for (vector<class Quest*>::iterator i = quests.begin(); i != quests.end(); i++)
		{
			if ((*i)->GetQuestStateID() == KILLWHOLEMONSTERS)
			{
				vector<class KillMonster>::iterator adress_of_begin_of_monsters_vector = (*(*i)->GetQuestState())->GetBeginOfMonstersToKill();
				vector<class KillMonster>::iterator adress_of_end_of_monsters_vector = (*(*i)->GetQuestState())->GetEndOfMonstersToKill();

				for (vector<class KillMonster>::iterator j = adress_of_begin_of_monsters_vector; j != adress_of_end_of_monsters_vector; j++)
				{
					if (mob->GetID() == (*j).GetMob()->GetID())
						(*j).IncAmount();
				}
			}
			(*i)->CheckRaiseQuestState();
		}
	}
}

HERO_ACT Hero::CheckAction()
{
	switch (_getch())
	{
		case 'E':
		case 'e':
			return HERO_ACT::TALK; break;
		case 'A':
		case 'a':
			return HERO_ACT::ATTACK; break;
		case 'I':
		case 'i':
			return HERO_ACT::OPEN_INVENTORY; break;
		case 'U':
		case 'u':
			return HERO_ACT::OPEN_EQ; break;
		case 'Y':
		case 'y':
			return HERO_ACT::OPEN_STATS; break;
		case 'N':
		case 'n':
			return HERO_ACT::OPEN_DIARY; break;
	}
	return NONE;
}

//void Warrior::StandardAttack(Mob* enemy)
//{
//	bool critical = false;
//	int hit = this->whole_attack_damage - enemy->defence;
//
//	if (rand() % 100 < this->whole_critical_hit_chance)
//	{
//		critical = true;
//		hit = hit*2;
//	}
//	enemy->hp -= hit;
//	ChangeColor(2);
//	cout << "Atakujesz z sila +" << whole_attack_damage << endl;
//	if (critical) cout << "Cios krytyczny! " << endl;
//	cout << enemy->GetName() << " otrzymuje " << hit << " obrazen, pozostalo " << "(" << (int)(((float)enemy->GetHp() / (float)enemy->GetMaxHp()) * 100.0) << "%)" << endl << endl;
//	ChangeColor(15);
//}

vector<class Mob*>::iterator Hero::TryAttack(vector <class Mob*>& monsters, int & number)
{
	int trying_x = pos_x, trying_y = pos_y;
	switch (DIR)
	{
	case UP: trying_y--; break;
	case DOWN: trying_y++; break;
	case LEFT: trying_x--; break;
	case RIGHT: trying_x++; break;
	}

	int ii = 0;
	if (!monsters.empty())
	{
		for (vector <class Mob*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		{
			if ((*i)->pos_x == trying_x && (*i)->pos_y == trying_y)
			{
				number = ii;
				return i;
			}
			ii++;
		}
	}

	return monsters.end();
}

void Hero::AddQuest(Quest * quest)
{
	quests.push_back(quest);
}

void Hero::Clr()
{
	gotoxy(pos_x, pos_y);
	char symbol = ' ';
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symbol, 1, 0, 0);
}

vector<class NPC*>::iterator Hero::TryTalk(vector<class NPC*>& _NPCs, int & number)
{
	int trying_x = pos_x, trying_y = pos_y;
	switch (DIR)
	{
		case UP: trying_y--; break;
		case DOWN: trying_y++; break;
		case LEFT: trying_x--; break;
		case RIGHT: trying_x++; break;
	}

	int ii = 0;
	if (!_NPCs.empty())
	{
		for (vector <class NPC*>::iterator i = _NPCs.begin(); i != _NPCs.end(); i++)
		{
			if ((*i)->pos_x == trying_x && (*i)->pos_y == trying_y)
			{
				number = ii;
				return i;
			}

			ii++;
		}
	}

	return _NPCs.end();
}