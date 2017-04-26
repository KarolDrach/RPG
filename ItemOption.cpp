#include "ItemOption.h"
#include "Globaldefs.h"

using namespace std;

ItemOption::ItemOption(ITEM_OPTION id)
{
	this->id = id;
	switch (id)
	{
		case USE: this->text = "Uzyj/zjedz"; break;
		case EQUIP: this->text = "Zaloz"; break;
		case DESTROY: this->text = "Zniszcz"; break;
	}
}
