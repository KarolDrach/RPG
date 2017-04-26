#pragma once
#include "Globaldefs.h"

using namespace std;

extern class Item;

class Equipment
{
protected:
	ITEM_TYPE selected;
	int top_margin;
	int left_margin;
	Item* armor, *shoes, *lefthand, *righthand, *head, *ring;
public:
	friend class Inventory;
	Equipment();
	void ShowEquipment();
	int WriteItemParameters(int x, int y, ITEM_TYPE type);
};