#pragma once
#include "Map.h"
#include "Globaldefs.h"
#include "Actor.h"
#include <vector>
#include <string>

extern class NPC;
extern class Hero;
extern class Fight;
extern class Warrior;
extern class Map;
extern class Loot;

using namespace std;

class Mob : public Actor
{
protected:
	char map_symbol;
	MOB_ID id;
public:
	friend class Hero;
	friend class Fight;
	friend class Warrior;
	friend class Map;
	virtual void InitPossibleLoots() = 0;
	virtual void test() {};
	Mob(int pos_x, int pos_y, int level, int whole_max_hp, int whole_max_mana, int whole_strength, int whole_attack_damage, int whole_defence, int whole_critical_hit_chance, string name, MOB_ID id,
		char map_symbol);
	~Mob();
	void Clr();
	MOB_ID GetID() { return id; }
};

class Rat : public Mob
{
public:
	friend class Map;
	virtual void InitPossibleLoots();
	Rat(int pos_x = 5,
		int pos_y = 5,
		int level = 1,
		int whole_max_hp = 50,
		int whole_max_mana = 0,
		int whole_strength = 5,
		int whole_attack_damage = 5,
		int whole_defence = 10,
		int whole_critical_hit_chance = 15,
		string name = "Szczur",
		char map_symbol = '@',
		MOB_ID id = RAT) :
		/*Actor(int pos_x, int pos_y, int level, int basic_max_hp, int basic_max_mana, int basic_strength, int basic_attack_damage, int basic_defence,
			int basic_critical_hit_chance, string name)*/
		Mob(pos_x, pos_y, level, whole_max_hp, whole_max_mana, whole_strength, whole_attack_damage, whole_defence, whole_critical_hit_chance, name, id, map_symbol) { InitPossibleLoots(); };
};

class Orc : public Mob
{
public:
	friend class Map;
	virtual void InitPossibleLoots();
	Orc(int pos_x = 5,
		int pos_y = 5,
		int level = 1,
		int basic_max_hp = 70,
		int basic_max_mana = 0,
		int basic_strength = 15,
		int basic_attack_damage = 20,
		int basic_defence = 8,
		int basic_critical_hit_chance = 15,
		string name = "Ork",
		char map_symbol = '&',
		MOB_ID id = ORC) :
		/*Actor(int pos_x, int pos_y, int level, int basic_max_hp, int basic_max_mana, int basic_strength, int basic_attack_damage, int basic_defence,
		int basic_critical_hit_chance, string name)*/
		Mob(pos_x, pos_y, level, basic_max_hp, basic_max_mana, basic_strength, basic_attack_damage, basic_defence, basic_critical_hit_chance, name, id, map_symbol) {
		InitPossibleLoots();
	};
};

//class Mob
//{
//protected:
//	int pos_x, pos_y;
//	int level;
//	int strength;
//	int hp;
//	int max_hp;
//	int basic_attack_damage;
//	int defence;
//	char map_symbol;
//	string name;
//	vector<Loot> possible_loots;
//	MOB_ID id;
//public:
//	friend class Hero;
//	friend class Fight;
//	friend class Warrior;
//	friend class Map;
//	virtual void InitPossibleLoots() = 0;
//	Mob(int pos_x, int pos_y, int level, int max_hp, char map_symbol, int basic_attack_damage, int defence, string name, MOB_ID id);
//	~Mob();
//	void Clr();
//	void StandardAttack(Hero* enemy);
//	string GetName() { return name; }
//	int GetHp() { return hp; }
//	int GetMaxHp() { return max_hp; }
//	int GetLevel() { return level; }
//	int GetBasicAttackDamage() { return basic_attack_damage; }
//	int GetDefence() { return defence; }
//	MOB_ID GetID() { return id; }
//};