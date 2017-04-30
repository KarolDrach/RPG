#include "Inventory.h"
#include "Globaldefs.h"
#include "ItemOption.h"
#include "Item.h"
#include "Bonus.h"
#include "Hero.h"
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iostream>

using namespace std;

Inventory::Inventory(int max_capacity)
{
	this->max_capacity = max_capacity;
	top_margin = 3;
	left_margin = 5;
	selected = 1;
	//items.reserve(max_capacity);
}

bool Inventory::operator+=(Item* item)
{
	if (items.size() + 1 <= max_capacity)
	{	
		items.push_back(item);
		return true;
	}
	else
	{
		return false;
	}
}

vector<Item*> Inventory::GetEquipmentAsVector()
{
	vector<Item*> result;
	if (equipment.armor != NULL) result.push_back(this->equipment.armor);
	if (equipment.head != NULL) result.push_back(this->equipment.head); 
	if (equipment.lefthand != NULL) result.push_back(this->equipment.lefthand);
	if (equipment.righthand != NULL) result.push_back(this->equipment.righthand);
	if (equipment.shoes != NULL) result.push_back(this->equipment.shoes);
	if (equipment.ring != NULL) result.push_back(this->equipment.ring);

	return result;
}

bool Inventory::HasFreeSlots()
{
	if (this->max_capacity == items.size())
		return false;
	else
		return true;
}

void Inventory::ShowInventory(Hero* & hero)
{
	std::system("cls");
	vector<class Item*>::iterator item_iterator;

	while(true)
	{ 
		vector<string> names;

		for (vector<class Item*>::iterator i = items.begin(); i != items.end(); i++)
		{
			names.push_back((*i)->GetName());
		}

		int temp_selected = DisplayListMenu(left_margin, top_margin, names, selected);

		if (temp_selected == -999)
			break;
		else
			selected = temp_selected;
				
		item_iterator = items.begin();
		for (int i = 1; i < selected; i++)
			item_iterator++;

		if (items.size() > 0)
		{
			ShowItemMenu(this->items.at(selected - 1), item_iterator, hero);
			if (item_iterator == items.end())
			{
				item_iterator = --items.end();
				selected = names.size() - 1;
			}
			ClearScreenFromXY(left_margin, top_margin, 85, 25);
		}
	}

	std:system("cls");
}

void Inventory::ShowItemMenu(Item* & item, vector<Item*>::iterator & item_iterator, Hero* & hero)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	gotoxy(left_margin + 20, top_margin);
	cout << item->name;
	gotoxy(left_margin + 20, top_margin + 2);
	cout << item->description;
	cout << endl << endl;
	gotoxy(left_margin + 20, top_margin + 3);
	int line_count = 1;
	for (vector<Bonus<>>::iterator i = (item->bonuses).begin(); i != (item->bonuses).end(); i++)
	{
		cout << (*i).text << (*i).value;
		gotoxy(left_margin + 20, top_margin + 3 + line_count);
		line_count++;
	}

	int selected = 1;
	int pos_menu_left = left_margin + 20,
		pos_menu_top = top_margin + 4 + (int)item->description.length() / 40 + (int)item->bonuses.capacity();

	vector<ItemOption> options_list;

	if (item->type == CONSUMABLE)
		options_list.push_back(ItemOption(USE));

	if (item->type == RIGHTHAND || item->type == LEFTHAND || item->type == HEAD || item->type == ARMOR || item->type == SHOES || item->type == RING)
		options_list.push_back(ItemOption(EQUIP));
	
	options_list.push_back(ItemOption(DESTROY));

	vector<string> option_textes_list;
	for (vector<ItemOption>::iterator i = options_list.begin(); i != options_list.end(); i++)
		option_textes_list.push_back((*i).text);

	int selected_option = DisplayListMenu(pos_menu_left, pos_menu_top, option_textes_list);
	if (selected_option != -999)
		UseOption(options_list.at(selected_option - 1).id, item_iterator, item, hero);
}

void Inventory::UseOption(ITEM_OPTION option, vector<Item*>::iterator & item_iterator, Item* & item, Hero* & hero)
{
	switch (option)
	{
		case DESTROY:
		{
			item_iterator = items.erase(item_iterator);
			break;
		}
		case EQUIP:
		{
			EquipItem(item_iterator);
			hero->RecalculateHeroStatsWithItems();
			break;
		}
		case USE:
		{
			item->ActivateEffect(hero);
			item_iterator = items.erase(item_iterator);
			break;
		}
		default:
			break;
	}
}

void Inventory::EquipItem(vector<Item*>::iterator& item_iterator)
{
	try
	{
		if ((*item_iterator)->type == CONSUMABLE)
			throw 1;

		switch ((*item_iterator)->type)
		{
			case HEAD:
			{
				if (equipment.head == NULL)
				{
					equipment.head = *item_iterator;
					item_iterator = items.erase(item_iterator);
				}
				else
				{
					SwapItemInventoryEquiped(item_iterator, HEAD);
				}
				break;
			}
			case SHOES:
			{
				if (equipment.shoes == NULL)
				{
					equipment.shoes = *item_iterator;
					item_iterator = items.erase(item_iterator);
				}
				else
				{
					SwapItemInventoryEquiped(item_iterator, SHOES);
				}
				break;
			}
			case RIGHTHAND:
			{
				if (equipment.righthand == NULL)
				{
					equipment.righthand = *item_iterator;
					item_iterator = items.erase(item_iterator);
				} 
				else
				{
					SwapItemInventoryEquiped(item_iterator, RIGHTHAND);
				}
				break;
			}
			case LEFTHAND:
			{
				if (equipment.lefthand == NULL)
				{
					equipment.lefthand = *item_iterator;
					item_iterator = items.erase(item_iterator);
				}
				else
				{
					SwapItemInventoryEquiped(item_iterator, LEFTHAND);
				}
				break;
			}
			case ARMOR:
			{
				if (equipment.armor == NULL)
				{
					equipment.armor = *item_iterator;
					item_iterator = items.erase(item_iterator);
				}
				else
				{
					SwapItemInventoryEquiped(item_iterator, ARMOR);
				}
				break;
			}
			case RING:
			{
				if (equipment.ring == NULL)
				{
					equipment.ring = *item_iterator;
					item_iterator = items.erase(item_iterator);
				}
				else
				{
					SwapItemInventoryEquiped(item_iterator, RING);
				}
				break;
			}

		}
	}
	catch (...)
	{
		cout << "Nie moze byc zalozony! To nie jest item typu EQUIP";
	}

}

void Inventory::SwapItemInventoryEquiped(vector<Item*>::iterator& item_iterator, ITEM_TYPE type)
{
	Item* from_equipment;
	switch (type)
	{
		case HEAD:
			from_equipment = equipment.head;
			break;
		case SHOES:
			from_equipment = equipment.shoes;
			break;
		case RIGHTHAND:
			from_equipment = equipment.righthand;
			break;
		case LEFTHAND:
			from_equipment = equipment.lefthand;
			break;
		case ARMOR:
			from_equipment = equipment.armor;
			break;
		case RING:
			from_equipment = equipment.ring;
			break;
		default:
			from_equipment = equipment.armor;
	}

	bool selection = false;
	bool enter_pushed_down = false;
	gotoxy(left_margin + 20, top_margin + 15);
	cout << "To miejsce w ekwipunku jest juz zajete przez " << from_equipment->GetName() << ".";
	gotoxy(left_margin + 20, top_margin + 16);
	cout << "Wymienic przedmioty?";
	gotoxy(left_margin + 20, top_margin + 17);

	while (!enter_pushed_down)
	{
		gotoxy(left_margin + 20, top_margin + 17);
		if (selection) ChangeColor(74);
		cout << "Tak";
		ChangeColor(15);
		cout << "         ";
		if (!selection) ChangeColor(74);
		cout << "Nie";
		ChangeColor(15);

		switch (_getch())
		{
			case 75:
			case 77:
				selection = !selection;
				break;
			case 13:
				enter_pushed_down = true;
		}
	}

	if (selection)
	{
		switch (type)
		{
		case HEAD:
			equipment.head = *item_iterator;
			break;
		case SHOES:
			equipment.shoes = *item_iterator;
			break;
		case RIGHTHAND:
			equipment.righthand = *item_iterator;
			break;
		case LEFTHAND:
			equipment.lefthand = *item_iterator;
			break;
		case ARMOR:
			equipment.armor = *item_iterator;
			break;
		case RING:
			equipment.ring = *item_iterator;
		}
		
		item_iterator = items.erase(item_iterator);
		items.push_back(from_equipment);
	}
}
