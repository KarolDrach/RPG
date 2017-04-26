#pragma once
#include "Mob.h"
#include "NPC.h"
#include "Obstacle.h"
#include <vector>

class Map
{
protected:
	int width, height;
	char border_symbol;
	vector <class Obstacle> obstacles;
	vector <class NPC*> NPCs;
	vector <class Mob*> monsters;
public:
	friend class Hero;
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	vector <class Obstacle>& GetObstacleVector() { return obstacles; }
	vector <class NPC*>& GetNPCVector() { return NPCs; }
	vector <class Mob*>& GetMobVector() { return monsters; }
	void DrawAllMobsHP();
	void AddObstacle(class Obstacle obstacle);
	void AddNPC(class NPC* npc);
	void AddMob(class Mob* mob);
	void DeleteObstacle(vector<class Obstacle>::iterator iterator);
	void DeleteMob(vector<class Mob*>::iterator iterator);
	void DeleteNPC(vector<class NPC*>::iterator iterator);
	void DrawBorder();
	void DrawInside();
	Map(int width, int height, char border_symbol);
};