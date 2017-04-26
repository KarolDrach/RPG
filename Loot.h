#pragma once
#include "Globaldefs.h"

extern class Item;

class Loot
{
protected:
	Item* loot;
	int percentage;
public:
	Loot(Item* item, int percentage);
	int GetPercentage() { return percentage; }
	Item* GetLoot() { return loot; }
};

