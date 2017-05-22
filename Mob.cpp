#include "Mob.h"
#include "Globaldefs.h"
#include "Hero.h"
#include "Item.h"
#include "Loot.h"
#include <Windows.h>

using namespace std;

Mob::Mob(int pos_x, int pos_y, int level, int whole_max_hp, int whole_max_mana, int whole_strength, int whole_attack_damage, int whole_defence, int whole_critical_hit_chance, string name, MOB_ID id, 
		 char map_symbol)
{
	actor_id = MONSTER;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->level = level;
	this->whole_max_hp = whole_max_hp;
	this->whole_max_mana = whole_max_mana;
	this->whole_strength = whole_strength;
	this->whole_attack_damage = whole_attack_damage;
	this->whole_defence = whole_defence;
	this->map_symbol = map_symbol;
	this->name = name;
	this->id = id;

	this->hp = whole_max_hp;
	this->mana = whole_max_mana;
}

Mob::~Mob()
{
	char space = ' ';
	gotoxy(this->pos_x, this->pos_y);
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &space, 1, 0, 0);
}

void Mob::Clr()
{
	gotoxy(pos_x, pos_y);
	char symbol = ' ';
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), &symbol, 1, 0, 0);
}

void Rat::InitPossibleLoots()
{
	this->possible_loots.push_back(class Loot(new class Meat, 100));
	this->possible_loots.push_back(class Loot(new class LeatherArmor, 40));
}

void Orc::InitPossibleLoots()
{
	this->possible_loots.push_back(class Loot(new class Meat, 100));
}
