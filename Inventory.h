#pragma once
#include "Globaldefs.h"
#include "Equipment.h"
#include <vector>

extern class Item;
extern class Equipment;
extern class Hero;

using namespace std;

class Inventory
{
public:
	class Equipment equipment;
protected:
	int max_capacity;
	int top_margin;
	int left_margin;
	int selected;
public:
	Inventory(int max_capacity = 15); 
	bool operator +=(class Item* item);
	vector<class Item*> items;
	vector<class Item*> GetEquipmentAsVector();
	int GetMaxCapacity() { return max_capacity; }
	bool HasFreeSlots();
	void ShowInventory(class Hero * & hero);
	void ShowItemMenu(class Item* & item, vector<class Item*>::iterator &item_iterator, class Hero* & hero);
	void UseOption(ITEM_OPTION option, vector<class Item*>::iterator & item_iterator, class Item* & item, class Hero* & hero);
	void EquipItem(vector<class Item*>::iterator& item_iterator);
	void SwapItemInventoryEquiped(vector<class Item*>::iterator& item_iterator, ITEM_TYPE type);
};