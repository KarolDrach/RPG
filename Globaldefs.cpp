#include "Globaldefs.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

void HideCursor()																			
{																							
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);								
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void ClearScreenFromXY(int start_x, int start_y, int width, int height)
{
	gotoxy(start_x, start_y);
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			cout << " ";
		}
		gotoxy(start_x, start_y + i);
	}
}

int CalculateNewLevelExp(int level)
{
	return (20 * level) + (3 * level * (level - 2)) + (level * level * level / 15);
}

bool DisplayYesNoMenu(int x, int y, string question)
{
	gotoxy(x, y);
	cout << question;
	bool enter_pushed_down = false;
	bool selection = true;
	while (!enter_pushed_down)
	{

		gotoxy(x + 5, y + 4);
		if (selection) ChangeColor(74);
		cout << "Tak";
		ChangeColor(15);
		cout << "         ";
		if (!selection) ChangeColor(74);
		cout << "Nie";
		ChangeColor(15);

		switch (_getch())
		{
		case 75:
		case 77:
			selection = !selection;
			break;
		case 13:
			enter_pushed_down = true;
		}
	}

	if (selection)
		return true;
	else
		return false;
}

void gotoxy(const int x, const int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ChangeColor(int numofcol)
{
	HANDLE hWyj;
	hWyj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hWyj, numofcol);
}