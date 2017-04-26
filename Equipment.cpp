#include "Globaldefs.h"
#include "Equipment.h"
#include "Item.h"
#include <conio.h>

using namespace std;

Equipment::Equipment()
{
	armor = NULL;
	shoes = NULL;
	lefthand = NULL;
	righthand = NULL;
	head = NULL;
	this->left_margin = 5;
	this->top_margin = 3;
	selected = ARMOR;
}

void Equipment::ShowEquipment()
{
	system("cls");
	ChangeColor(15);
	bool close_window = false;

	while (!close_window)
	{
		int height_of_item_bonuses = 0;
		gotoxy(left_margin, top_margin);

		if (selected == ARMOR && armor != NULL) ChangeColor(112);
		cout << "Zbroja:     "; if (armor != NULL)		cout << armor->GetName();	   
		if (selected == ARMOR && armor != NULL)
		{
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, ARMOR);
			ChangeColor(15);
		}
		gotoxy(left_margin, top_margin + 1);

		if (selected == SHOES && shoes != NULL) ChangeColor(112);
		cout << "Buty:       "; if (shoes != NULL)		cout << shoes->GetName();	   
		if (selected == SHOES && shoes != NULL)
		{
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, SHOES);
			ChangeColor(15);
		}
		gotoxy(left_margin, top_margin + 2);

		if (selected == HEAD && shoes != NULL) ChangeColor(112);
		cout << "Helm:       "; if (head != NULL)		cout << head->GetName();	   
		if (selected == HEAD && shoes != NULL)
		{
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, HEAD);
			ChangeColor(15);
		}
		gotoxy(left_margin, top_margin + 3);

		if (selected == RIGHTHAND && righthand != NULL) ChangeColor(112);
		cout << "Prawa reka: "; if (righthand != NULL)  cout << righthand->GetName();  
		if (selected == RIGHTHAND && righthand !=  NULL)
		{
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, RIGHTHAND);
			ChangeColor(15);
		}
		gotoxy(left_margin, top_margin + 4);

		if (selected == LEFTHAND && lefthand != NULL) ChangeColor(112);
		cout << "Lewa reka:  "; if (lefthand != NULL)	cout << lefthand->GetName();   
		if (selected == LEFTHAND && lefthand != NULL)
		{
			ChangeColor(15);
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, LEFTHAND);
		}
		gotoxy(left_margin, top_margin + 5);

		if (selected == RING && ring != NULL) ChangeColor(112);
		cout << "Pierscien:  "; if (ring != NULL)	cout << ring->GetName();
		if (selected == RING && ring != NULL)
		{
			ChangeColor(15);
			height_of_item_bonuses = WriteItemParameters(left_margin + 35, top_margin, RING);
		}
		gotoxy(left_margin, top_margin + 6);

		cout << endl << endl;
		cout << "ESC aby wyjsc.";

		switch (_getch())
		{
			case 72:      // KEY UP
			{
				if (selected == ARMOR) selected = RING;
				else if (selected == SHOES) selected = ARMOR;
				else if (selected == HEAD) selected = SHOES;
				else if (selected == RIGHTHAND) selected = HEAD;
				else if (selected == LEFTHAND) selected = RIGHTHAND;
				else if (selected == RING) selected = LEFTHAND;
				break;
			}
			case 80:     // KEY DOWN
			{
				if (selected == ARMOR) selected = SHOES;
				else if (selected == SHOES) selected = HEAD;
				else if (selected == HEAD) selected = RIGHTHAND;
				else if (selected == RIGHTHAND) selected = LEFTHAND;
				else if (selected == LEFTHAND) selected = RING;
				else if (selected == RING) selected = ARMOR;
				break;
			}
			case 27:
			{
				close_window = true;
				break;
			}		
		}

		if (!close_window) ClearScreenFromXY(left_margin + 35, top_margin, 40, height_of_item_bonuses);
	}		
	system("cls");
}

int Equipment::WriteItemParameters(int x, int y, ITEM_TYPE type)        // FUNCTION RETURNS THE NUMBER OF LINES THAT IT WROTE
{
	int number_of_lines = 1;
	ChangeColor(15);
	gotoxy(x, y);
	vector<class Bonus<>> item_bonuses;
	switch (type)
	{
		case ARMOR:
			cout << armor->GetDescription();
			item_bonuses = armor->GetBonusesVector();
			break;
		case SHOES:
			cout << shoes->GetDescription();
			item_bonuses = shoes->GetBonusesVector();
			break;
		case HEAD:
			cout << head->GetDescription();
			item_bonuses = head->GetBonusesVector();
			break;
		case RIGHTHAND:
			cout << righthand->GetDescription();
			item_bonuses = righthand->GetBonusesVector();
			break;
		case LEFTHAND:
			cout << lefthand->GetDescription();
			item_bonuses = lefthand->GetBonusesVector();
			break;
		case RING:
			cout << ring->GetDescription();
			item_bonuses = ring->GetBonusesVector();
	}

	int actual_relative_line = 0;

	for (vector<class Bonus<>>::iterator i = item_bonuses.begin(); i != item_bonuses.end(); i++)
	{
		gotoxy(x, y + 2 + actual_relative_line);
		cout << (*i).GetText() << (*i).GetValueOfType();
		number_of_lines++;
		actual_relative_line++;
	}

	return number_of_lines + 2;
}
