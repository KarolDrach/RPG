#include "Actor.h"
#include <string>
#include <conio.h>

using namespace std;

Actor::Actor(int pos_x, int pos_y, int level, int basic_max_hp, int basic_max_mana, int basic_strength, int basic_attack_damage, int basic_defence, 
		     int basic_critical_hit_chance, string name)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->level = level;
	this->basic_attack_damage = basic_attack_damage;
	this->basic_critical_hit_chance = basic_critical_hit_chance;
	this->basic_defence = basic_defence;
	this->basic_max_hp = basic_max_hp;
	this->basic_max_mana = basic_max_mana;
	this->basic_strength = basic_strength;
	this->hp = basic_max_hp;
	this->mana = basic_max_mana;

	this->actual_experience = 0;
	this->next_level_experience = CalculateNewLevelExp(level);
}

void Actor::AddExperience(int amount)
{
	actual_experience += amount;

	while (actual_experience >= next_level_experience)
	{
		actual_experience -= next_level_experience;
		this->LevelUp();
	}

	
}

void Actor::LevelUp()
{
	this->level++;
	next_level_experience = CalculateNewLevelExp(level);
	this->skill_points_to_distribute += 1;
	this->stat_points_to_distribute += 5;

	//ANIMATION 
	std::system("cls");
	
	ChangeColor(14);
	gotoxy(6, 3);
	cout << "###         #########      ###           ###     #########   ###             ###       ###     #########   " << endl;
	gotoxy(6, 4);
	cout << "###         #########      ###           ###     #########   ###             ###       ###     ###    ###	" << endl;
	gotoxy(6, 5);
	cout << "###         ###             ###         ###      ###         ###             ###       ###     ###     ###	" << endl;
	gotoxy(6, 6);
	cout << "###         ###             ###         ###      ###         ###             ###       ###     ###     ###	" << endl;
	gotoxy(6, 7);
	cout << "###         #########        ###       ###       #######     ###             ###       ###     ###   ###	" << endl;
	gotoxy(6, 8);
	cout << "###         #########        ###       ###       #######     ###             ###       ###     #######	    " << endl;
	gotoxy(6, 9);
	cout << "###         ###               ###     ###        ###         ###             ###       ###     ###			" << endl;
	gotoxy(6, 10);
	cout << "###         ###               ###     ###        ###         ###             ###       ###     ###			" << endl;
	gotoxy(6, 11);
	cout << "###         ###                ###   ###         ###         ###              ###     ###      ###			" << endl;
	gotoxy(6, 12);
	cout << "########    ##########         ###   ###         #########   #########         #########       ###			" << endl;
	gotoxy(6, 13);
	cout << "########    ##########          #######          #########   #########          #######        ###			" << endl;
	gotoxy(6, 14);

	ChangeColor(13);
	gotoxy(14, 17);
	cout << "Awansowales na poziom " << this->level << "! Otrzymales jeden punkt umiejetnosci i piec punktow statystyk." << endl;

	bool close_stat_points_distribution = false;
	bool close_skill_points_distribution = false;

	int selection = 1;
	int temp_strength_add = 0;
	int temp_dext_add = 0;
	int temp_int_add = 0;
	int temp_all_stat_points = stat_points_to_distribute;

	gotoxy(10, 19);
	ChangeColor(15);
	cout << "Pozostale punkty statystyk:";

	while (!close_stat_points_distribution)
	{
		gotoxy(40, 19);
		ChangeColor(15);
		cout << temp_all_stat_points;
		cout << "  TMPSTR " << temp_strength_add << "  TMPDXT " << temp_dext_add << "  TMP_INT " << temp_int_add << " SELECT " << selection << " BOOL" << close_stat_points_distribution;
		
		ClearScreenFromXY(15, 20, 150, 1);
		if (selection == 1)
			ChangeColor(112);
		
		gotoxy(10, 20);
		cout << "Sila "; for (int i = 0; i < temp_strength_add; i++) cout << "+";
		ChangeColor(15);

		ClearScreenFromXY(20, 21, 150, 1);
		if (selection == 2)
			ChangeColor(112);
			
		gotoxy(10, 21);
		cout << "Zrecznosc "; for (int i = 0; i < temp_dext_add; i++) cout << "+";
		ChangeColor(15);

		ClearScreenFromXY(19, 22, 150, 1);
		if (selection == 3)
			ChangeColor(112);
				
		gotoxy(10, 22);
		cout << "Intelekt "; for (int i = 0; i < temp_int_add; i++) cout << "+";
		ChangeColor(15);

		if (selection == 4)
			ChangeColor(112);
			
		gotoxy(10, 23);
		cout << "Akceptuj";
		ChangeColor(15);

		switch (_getch())
		{
			case 72:      // KEY UP
			{
				selection--;
				if (!selection) selection = 4;
				break;
			}
			case 80:     // KEY DOWN
			{
				selection++;
				if (selection == 5) selection = 1;
				break;
			}
			case 77:     // KEY RIGHT
			{				
				if (temp_all_stat_points > 0)
				{
					temp_all_stat_points--;

					switch (selection)
					{
						case 1:
							temp_strength_add++;
							break;
						case 2:
							temp_dext_add++;
							break;
						case 3:
							temp_int_add++;
							break;
					}
				}
					
				break;
			}
			case 75:	// KEY LEFT
			{		
				if (temp_all_stat_points < stat_points_to_distribute && temp_all_stat_points >= 0)
				{		
					switch (selection)
					{
						case 1:
						{
							if (temp_strength_add > 0)
							{
								temp_strength_add--;
								temp_all_stat_points++;
							}
							break;
						}		
						case 2:
						{
							if (temp_dext_add > 0)
							{
								temp_dext_add--;
								temp_all_stat_points++;
							}
							break;
						}						
						case 3:
						{
							if (temp_int_add > 0)
							{
								temp_int_add--;
								temp_all_stat_points++;
							}
							break;
						}					
					}
				}
				break;
			}
			case 13:   // KEY ENTER
			{
				if (selection == 4)
				{																	
					if (DisplayYesNoMenu(9, 28, "Akceptowac/pominac? Niewydane punkty mozesz potem dodac w menu statystyk postaci."))
						close_stat_points_distribution = true;

					ClearScreenFromXY(4, 28, 100, 3);															
					break;
				}
			}
		}
	}

	this->basic_strength += temp_strength_add;
	this->basic_dexterity += temp_dext_add;
	this->basic_intelligence += temp_int_add;
	this->stat_points_to_distribute -= (temp_strength_add + temp_dext_add + temp_int_add);
	system("cls");
	ChangeColor(15);
}

void Actor::StandardAttack(class Actor * enemy)
{
	bool critical = false;
	bool piercing = true;
	int hit = this->whole_attack_damage;  // THIS IS BASIC VALUE OF HIT
	int pure_hit;						  // THIS IS PURE VALUE OF HIT, AFTER CALCULATING ATTACKER'S BONUSES LIKE CRITICAL ETC., BUT BEFORE CALCULATING DEFENSE OF HIT TAKER
	
	// CALCULATING CRITICAL HIT CHANCE
	if (rand() % 100 < this->whole_critical_hit_chance)
	{
		critical = true;
		hit = hit*2;
	}

	pure_hit = hit;
	// SUBSTRACTING DEFENCE WHEN NOT PIERCING HIT
	if (!(rand() % 100 < this->whole_piercing_hit_chance))
	{
		hit -= enemy->whole_defence;
		piercing = false;
	}
		
	if (hit < 0)
		hit = 0;

	enemy->hp -= hit;

	if (this->actor_id == PLAYER)
		ChangeColor(2);
	else
		ChangeColor(1);

	cout << this->GetName() << " atakuje z sila +" << pure_hit << endl;
	if (critical) cout << "- Cios krytyczny! " << endl;
	if (piercing) cout << "- Przeszywajacy cios!" << endl;
	cout << enemy->GetName() << " otrzymuje " << hit << " obrazen, pozostalo " << "(" << (int)(((float)enemy->GetHp() / (float)enemy->GetMaxHp()) * 100.0) << "%) HP." << endl << endl;
	ChangeColor(15);
}

void Actor::AddToInventory(class Item* item)
{
	inventory += item;
}

void Actor::AddToInventory(class Item * item, int amount)
{
	for (int i = 1; i <= amount;)
	{
		if (inventory += item)
			i++;
		else
			break;
	}

}
