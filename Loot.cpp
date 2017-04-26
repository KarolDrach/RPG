#include "stdafx.h"
#include "Loot.h"
#include "Item.h"

Loot::Loot(class Item * item, int percentage)
{
	this->loot = item;
	this->percentage = percentage;
}