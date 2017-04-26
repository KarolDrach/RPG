#pragma once
#include "Globaldefs.h"
#include <vector>

extern class Map;
extern class Hero;

class Obstacle
{
protected:
	char map_symbol;
	int color;
	int pos_x;
	int pos_y;
public:
	friend class Map;
	friend class Hero;
	Obstacle(int pos_x = 1, int pos_y = 1, char map_symbol = (char)219, int color = 15);
};

