#pragma once
#include "Globaldefs.h"
#include "Inventory.h"
#include "Loot.h"
#include <string>

using namespace std;

class Actor
{
public:
	Inventory inventory;
	vector<class Loot> possible_loots;
protected:
	ACTOR_ID actor_id;
	int skill_points_to_distribute;
	int stat_points_to_distribute;
	int pos_x, pos_y;
	int level;
	int hp;
	int basic_max_hp;
	int mana;
	int basic_max_mana;
	int basic_strength;
	int basic_dexterity;
	int basic_intelligence;
	int basic_attack_damage;
	int basic_defence;
	int basic_critical_hit_chance;
	int basic_piercing_hit_chance;
	int whole_max_hp;
	int whole_max_mana;
	int whole_strength;
	int whole_dexterity;
	int whole_intelligence;
	int whole_attack_damage;
	int whole_defence;
	int whole_critical_hit_chance;
	int whole_piercing_hit_chance;
	int actual_experience;
	int next_level_experience;
	string name;
public:
	friend class Mob;
	friend class Fight;
	Actor(int pos_x = 10, int pos_y = 0, int level = 0, int basic_max_hp = 0, int basic_max_mana = 0, int basic_strength = 0, int basic_attack_damage = 0,
		  int basic_defence = 0, int basic_critical_hit_chance = 0, string name = "A");
	void StandardAttack(class Actor* enemy);
	void LevelUp();
	string GetName() { return name; }
	int GetHp() { return hp; }
	int GetBasicMaxHP() { return basic_max_hp; }
	int GetMaxHp() { return whole_max_hp; }	
	int GetMana() { return mana; }
	int GetMaxMana() { return whole_max_mana; }
	int GetBasicMaxMana() { return basic_max_mana; }	
	int GetBasicStrength() { return basic_strength; }
	int GetBasicAttackDamage() { return basic_attack_damage; }
	int GetBasicDefence() { return basic_defence; }
	int GetBasicCriticalHitChance() { return basic_critical_hit_chance; }		
	int GetWholeStrength() { return whole_strength; }
	int GetWholeAttackDamage() { return whole_attack_damage; }
	int GetWholeDefence() { return whole_defence; }
	int GetWholeCriticalHitChance() { return whole_critical_hit_chance; }
	int GetLevel() { return level; }
	int GetActualExperience() { return actual_experience; }
	int GetNextLevelExperience() { return next_level_experience; }
	void AddToInventory(class Item* item);
	void AddToInventory(class Item* item, int amount);
	void AddExperience(int amount);
	void AddHp(int hp) { ((this->hp + hp) > this->whole_max_hp) ? this->hp = whole_max_hp : this->hp += hp; };
	void AddMana(int mana) { ((this->mana + mana) > this->whole_max_mana) ? this->mana = whole_max_mana : this->mana += mana; };
	virtual ~Actor() {};
};

