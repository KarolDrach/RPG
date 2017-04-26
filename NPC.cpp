#include "NPC.h"
#include "Globaldefs.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

NPC::NPC(int pos_x, int pos_y, int level, string name, char map_symbol, int color)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->level = level;
	this->name = name;
	this->map_symbol = map_symbol;
	this->color = color;
}

void NPC::Say(string text, bool display_who)
{
	if (display_who)
	{
		ChangeColor(2);
		cout << this->name << ": ";
		ChangeColor(15);
	}

	cout << text;
}

void Villager::Talk()
{
	bool badkey_flag = true;
	system("cls");
	cout << endl;

	this->Say("Co robisz w tych lochach? Tu jest szalenie niebezpiecznie!", true);

	cout << endl << endl << "1. A kim TY jestes?" << endl;
	cout << "2. To wspaniale. Jakies rady?" << endl;

	while (badkey_flag)
	{
		switch (_getch())
		{
		case '1': {system("cls"); cout << endl; this->Say("Ja jestem straznikiem. Jak tak bardzo chcesz, nie bede cie zatrzymywal,\n ale czuj sie ostrzezony!", true); cout << endl; badkey_flag = false;  break; }
		case '2': {system("cls"); cout << endl; this->Say("Widzisz te rozowa skrzynie? Otworz ja, moze znajdziesz tam cos ciekawego.", true); cout << endl; badkey_flag = false; break; }
		}
	}
	_getch();
	system("cls");
}

void Chest::Talk()
{
	bool badkey_flag = true;
	bool wait_after_display_last_dialogue = true;
	system("cls");
	cout << endl;
	this->Say("Widzisz stara, zakurzona skrzynie.", false); 
	if (!flag_opened)
		cout << endl << endl << "1. Otwieram." << endl;
	else
		cout << " Jest otwarta, a w srodku nic nie ma" << endl;

	cout << "2. Odchodze." << endl;

	while (badkey_flag)
	{
		switch (_getch())
		{
		case '1': {if (!flag_opened) { system("cls"); cout << endl; this->Say("W skrzyni znajdujesz jakis przedmiot!", false); this->flag_opened = true; badkey_flag = false; break; }}
		case '2': {badkey_flag = false; wait_after_display_last_dialogue = false; break; }
		}
	}

	if(wait_after_display_last_dialogue) _getch();
	system("cls");
}
