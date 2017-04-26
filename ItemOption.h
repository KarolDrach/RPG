#pragma once
#include "Globaldefs.h"
#include <string>

extern class Inventory;
extern class Item;

using namespace std;

class ItemOption
{
protected:
	string text;
	ITEM_OPTION id;
public:
	ItemOption(ITEM_OPTION id);
	friend class Inventory;
	friend class Item;
};