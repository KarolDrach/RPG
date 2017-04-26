#pragma once
#include "Globaldefs.h"
#include "Bonus.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Item
{
protected:
	string name;
	ITEM_TYPE type;
	string description;
	vector<class Bonus<>> bonuses;
public:
	Item(const class Item* item);
	Item(string name, string description, ITEM_TYPE type, vector<class Bonus<>> bonuses);
	vector<class Bonus<>>& GetBonusesVector() { return bonuses; }
	string GetName() { return name; }
	string GetDescription() { return description; }
	ITEM_TYPE GetType() { return type; }
	virtual void InitBonuses() = 0;
	virtual void ActivateEffect(class Hero* _hero) = 0;
	friend class Inventory;
	virtual ~Item() {};
};

class Meat : public Item
{
public:
	virtual void InitBonuses() {};
	virtual void ActivateEffect(class Hero* _hero);
	Meat(string name = "Mieso",
		 string description = "Przywraca 15 hp.",
		 ITEM_TYPE type = CONSUMABLE,
		 vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
		 Item(name, description, type, bonuses) {};
};

class ManaMixture : public Item
{
public:
	virtual void InitBonuses() {};
	virtual void ActivateEffect(class Hero* _hero);
	ManaMixture(string name = "Mikstura many", 
				string description = "Przywraca 15 many.", 
				ITEM_TYPE type = CONSUMABLE, 
				vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
				Item(name, description, type, bonuses) {};
};

class LeatherArmor : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	LeatherArmor(string name = "Skorzana zbroja", 
				 string description = "Prosta, skorzana zbroja.", 
				 ITEM_TYPE type = ARMOR, 
				 vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
				 Item(name, description, type, bonuses) { InitBonuses(); };
};

class LeatherShoes : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	LeatherShoes(string name = "Skorzane buty", 
				 string description = "Solidne, skorzane buty.", 
				 ITEM_TYPE type = SHOES, 
				 vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
				 Item(name, description, type, bonuses) { InitBonuses(); };
};

class LeatherHelmet : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	LeatherHelmet(string name = "Skorzany helm", 
				  string description = "Wygodny helm z cielecej skory.", 
				  ITEM_TYPE type = HEAD, 
				  vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
				  Item(name, description, type, bonuses) { InitBonuses(); };
};

class Sword : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	Sword(string name = "Miecz", 
		  string description = "Zwykly miecz.", 
		  ITEM_TYPE type = RIGHTHAND, 
		  vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
		  Item(name, description, type, bonuses) { InitBonuses(); };
};

class SimpleShield : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	SimpleShield(string name = "Prosta tarcza", 
				 string description = "Zwykla tarcza.", 
				 ITEM_TYPE type = LEFTHAND, 
				 vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
				 Item(name, description, type, bonuses) { InitBonuses(); };
};

class GoldRing : public Item
{
	virtual void InitBonuses();
	virtual void ActivateEffect(class Hero* _hero) {};
public:
	GoldRing(string name = "Zloty pierscien",
		string description = "Pierscien z drogiego kruszcu. Moze byc sprzedany za wysoka cene.",
		ITEM_TYPE type = RING,
		vector<class Bonus<>> bonuses = vector<class Bonus<>>(0)) :
		Item(name, description, type, bonuses) {
		InitBonuses();
	};
};