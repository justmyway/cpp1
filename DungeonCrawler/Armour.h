#pragma once

#include "CarryItem.h"

class Armour
	: public CarryItem
{
public:
	Armour(string, string, int, int, int, int);
	~Armour();

	bool StillValid();
	Armour * Clone();
};

