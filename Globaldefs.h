#ifndef Globaldefs_h
#define Globaldefs_h

#include <vector>
#include <iostream>
#include <string>

enum HERO_DIR     { UP, DOWN, LEFT, RIGHT };
enum HERO_ACT     { NONE, ATTACK, TALK, OPEN_INVENTORY, OPEN_EQ, OPEN_STATS, OPEN_DIARY };
enum FIGHT_OPT    { BASIC_ATTACK, SKILL, FORWARD, WAITING };
enum ITEM_TYPE    { CONSUMABLE, RIGHTHAND, LEFTHAND, HEAD, ARMOR, SHOES, RING };
enum ITEM_OPTION  { USE, EQUIP, DESTROY };
enum BONUS_TYPE   { NO_BONUS, ADD_STRENGTH, ADD_DEXTERITY, ADD_INTELLIGENCE, ADD_MAX_HP, ADD_MAX_MANA, ADD_ATTACK_DAMAGE, ADD_DEFENCE, ADD_CRITICAL_HIT_CHANCE, ADD_PIERCING_HIT_CHANCE };
enum MOB_ID       { RAT, ORC };
enum OBJECTIVE_ID { KILLWHOLEMONSTERS, REACHXY};
enum ACTOR_ID     { MONSTER, NPC, PLAYER };

void ChangeColor(int numofcol);
void gotoxy(const int x, const int y);
void HideCursor();
void ClearScreenFromXY(int start_x, int start_y, int width, int height);
int CalculateNewLevelExp(int level);
bool DisplayYesNoMenu(int x, int y, std::string question);

// Colors for ChangeColor() function																				
//0 - czarny			-  black
//1 - niebieski			-  blue	
//2 - zielony			-  green
//3 - b喚kitny			-  azure
//4 - czerwony			-  red
//5 - purpurowy			-  purple
//6 - 鄴速y				-  yellow	
//7 - bia造				-  white
//8 - szary				-  grey
//9 - jasnoniebieski	-  light blue
//10 - jasnozielony		-  light green
//11 - jasnob喚kitny	-  light azure
//12 - jasnoczerwony	-  light red
//13 - jasnopurpurowy   -  light purple
//14 - jasno鄴速y		-  light yellow
//15 - jaskrawobia造	-  light white(??)
#endif