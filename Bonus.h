#pragma once
#include "Globaldefs.h"
#include <string>

using namespace std;

template <typename Bonus_value_type = int> 
class Bonus
{
protected:
	BONUS_TYPE type;
	Bonus_value_type value;
	string text;
public:
	Bonus(BONUS_TYPE type = NO_BONUS, Bonus_value_type value = (Bonus_value_type)0)
	{
		this->type = type;
		this->value = value;
		switch (type)
		{
			case ADD_STRENGTH: text = "Sila +"; break;
			case ADD_DEXTERITY: text = "Zrecznosc +"; break;
			case ADD_INTELLIGENCE: text = "Intelekt +"; break;
			case ADD_MAX_HP: text = "Max hp +"; break;
			case ADD_MAX_MANA: text = "Max mana +"; break;
			case ADD_ATTACK_DAMAGE: text = "Atak +"; break;
			case ADD_DEFENCE: text = "Obrona +"; break;
			case ADD_CRITICAL_HIT_CHANCE: text = "Cios krytyczny +"; break;
			case ADD_PIERCING_HIT_CHANCE: text = "Przebicie pancerza +"; break;
			default: break;
		}
	}
	BONUS_TYPE GetType() { return type; }
	string GetText() { return text; }
	Bonus_value_type GetValueOfType() { return value; }
	friend class Item;
	friend class Inventory;
};
