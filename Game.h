#ifndef Game_h
#define Game_h
#include "Globaldefs.h"
#include "Fight.h"

//extern class Hero;
//extern class Map;
//extern class Fight;
//extern class Actor;

using namespace std;

class Game
{
	bool Playing;
	bool map_need_to_be_refreshed;
	Hero* hero;
	Map* map;
	Fight FIGHT;
public:
	Game();
	void Lost();
	void InitializeMapManually();
	void InitializeHeroManually();
	bool InitializeHeroInventoryManually();
	void SetPlaying(bool arg) { Playing = arg; }
	bool GetPlaying() { return Playing; }
	void MainGame();
};
#endif