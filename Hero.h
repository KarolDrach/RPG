#ifndef Hero_h
#define Hero_h
#include "Globaldefs.h"
#include "Actor.h"
#include <vector>

using namespace std;

class Hero : public Actor
{
public:
	vector<class Quest*> quests;
protected:
	HERO_DIR DIR;
public:
	friend class Mob;
	friend class Fight;
	Hero(int pos_x = 10, int pos_y = 0, int level = 0, string name = "A");
	void AddQuest(class Quest* quest);
	void Clr();
	void Draw();
	void DrawHpManaBar(int map_height);
	void CheckMove(class Map & map);
	void RecalculateHeroStatsWithItems();
	void ShowHeroStats();
	void ShowDiary();
	void AddKilledMobToMissions(class Mob* mob);
	HERO_ACT CheckAction();
	vector<class Mob*>::iterator TryAttack(vector <class Mob*>& monsters, int & number);
	vector<class NPC*>::iterator TryTalk(vector <class NPC*>& _NPCs, int & number);
};
#endif

//class Hero
//{
//public:
//	Inventory inventory;
//	vector<Quest*> quests;
//protected:
//	int pos_x, pos_y;
//	int level;
//	int hp;
//	int basic_max_hp;
//	int whole_max_hp;
//	int mana;
//	int basic_max_mana;
//	int whole_max_mana;
//	int basic_strength;
//	int whole_strength;
//	int basic_attack_damage;
//	int whole_attack_damage;
//	int basic_defence;
//	int whole_defence;
//	int basic_critical_hit_chance;
//	int whole_critical_hit_chance;
//	string name;
//	HERO_DIR DIR;
//public:
//	friend class Mob;
//	friend class Fight;
//	Hero(int pos_x = 10, int pos_y = 0, int level = 0, string name = "A");
//	virtual void StandardAttack(Mob* enemy) = 0;
//	string GetName() { return name; }
//	int GetHp() { return hp; }
//	int GetMaxHp() { return whole_max_hp; }
//	void AddHp(int hp) { ((this->hp + hp) > this->whole_max_hp) ? this->hp = whole_max_hp : this->hp += hp; };
//	int GetMana() { return mana; }
//	int GetMaxMana() { return whole_max_mana; }
//	void AddMana(int mana) { ((this->mana + mana) > this->whole_max_mana) ? this->mana = whole_max_mana : this->mana += mana; };
//	int GetBasicStrength() { return basic_strength; }
//	int GetWholeStrength() { return whole_strength; }
//	int GetBasicAttackDamage() { return basic_attack_damage; }
//	int GetWholeAttackDamage() { return whole_attack_damage; }
//	int GetBasicDefence() { return basic_defence; }
//	int GetWholeDefence() { return whole_defence; }
//	int GetBasicCriticalHitChance() { return basic_critical_hit_chance; }
//	int GetWholeCriticalHitChance() { return whole_critical_hit_chance; }
//	void AddToInventory(Item* item);
//	void AddToInventory(Item* item, int amount);
//	void AddQuest(Quest* quest);
//	void Clr();
//	void Draw();
//	void DrawHpManaBar(int map_height);
//	void CheckMove(Map & map);
//	void RecalculateHeroStatsWithItems();
//	void ShowHeroStats();
//	void ShowDiary();
//	void AddKilledMobToMissions(Mob* mob);
//	HERO_ACT CheckAction();
//	vector<Mob*>::iterator TryAttack(vector <Mob*>& monsters, int & number);
//	vector<NPC*>::iterator TryTalk(vector <NPC*>& _NPCs, int & number);
//	virtual ~Hero() {};
//};