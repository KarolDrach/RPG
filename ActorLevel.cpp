#include "stdafx.h"
#include "ActorLevel.h"


ActorLevel::ActorLevel()
{
	for (int i = 0; i <= 99; i++)
	{
		if (i == 0 || i == 1)
			level_caps[i] = 0;
		else
			level_caps[i] = 20 * i + 3 * i*(i - 2);
	}
}


ActorLevel::~ActorLevel()
{
}
