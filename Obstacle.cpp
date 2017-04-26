#include "Obstacle.h"

Obstacle::Obstacle(int pos_x, int pos_y, char map_symbol, int color)
{
	this->map_symbol = map_symbol;
	this->color = color;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}
