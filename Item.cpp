#include "Item.h"
#include "Globaldefs.h"
#include "Bonus.h"
#include "Hero.h"
#include <iostream>

using namespace std;

// METHODS OF ABSTRACT CLASS ITEM

Item::Item(const Item * item)
{
	this->bonuses = item->bonuses;
	this->description = item->description;
	this->name = item->name;
	this->type = item->type;
}

Item::Item(string name, string description, ITEM_TYPE type, vector<Bonus<>> bonuses)
{
	this->name = name;
	this->description = description;
	this->type = type;
	this->bonuses = bonuses;
}

void Meat::ActivateEffect(Hero * _hero)
{
	_hero->AddHp(15);
}

void LeatherArmor::InitBonuses()
{
	this->bonuses.push_back(Bonus<>(ADD_DEFENCE, 6));
}

void ManaMixture::ActivateEffect(Hero * _hero)
{
	_hero->AddMana(15);
}

void LeatherShoes::InitBonuses()
{
	bonuses.push_back(Bonus<>(ADD_MAX_HP, 10));
	bonuses.push_back(Bonus<>(ADD_DEXTERITY, 5));
}

void LeatherHelmet::InitBonuses()
{
	bonuses.push_back(Bonus<>(ADD_MAX_HP, 5));
	bonuses.push_back(Bonus<>(ADD_INTELLIGENCE, 7));
}

void Sword::InitBonuses()
{
	bonuses.push_back(Bonus<>(ADD_ATTACK_DAMAGE, 20));
	bonuses.push_back(Bonus<>(ADD_PIERCING_HIT_CHANCE, 10));
}

void SimpleShield::InitBonuses()
{
	bonuses.push_back(Bonus<>(ADD_MAX_HP, 15));
}

void GoldRing::InitBonuses()
{
	bonuses.push_back(Bonus<>(ADD_CRITICAL_HIT_CHANCE, 15));
	bonuses.push_back(Bonus<>(ADD_PIERCING_HIT_CHANCE, 20));
}
