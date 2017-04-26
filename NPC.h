#pragma once
#include "Globaldefs.h"
#include "Map.h"
#include <vector>
#include <string>
#include <iostream>

extern class Mob;

using namespace std;

class NPC
{
protected:
	int pos_x, pos_y;
	int level;
	string name;
	char map_symbol;
	int color;
public:
	NPC(int pos_x = 1, int pos_y = 1, int level = 1, string name = "NPC", char map_symbol = '!', int color = 2);
	void Say(string text, bool display_who);
	virtual void Talk() = 0;
	friend class Map;
	friend class Hero;
	virtual ~NPC() {};
};

class Villager : public NPC
{
public:
	virtual void Talk();
	Villager(int pos_x = 1, int pos_y = 1, int level = 1, string name = "Straznik", char map_symbol = '!', int color = 2) :NPC(pos_x, pos_y, level, name, map_symbol, color) {};
	friend class Map;
};

class Chest : public NPC
{
private:
	bool flag_opened;
public:
	virtual void Talk();
	Chest(int pos_x = 1, int pos_y = 1, int level = 1, string name = "Skrzynia", char map_symbol = '!', int color = 13) :NPC(pos_x, pos_y, level, name, map_symbol, color) { flag_opened = false; };
	friend class Map;
};
