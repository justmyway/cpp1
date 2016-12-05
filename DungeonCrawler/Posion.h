#pragma once

#include "CarryItem.h"

class Posion :
	public CarryItem
{
public:
	Posion(string, string, int, int, int, int);
	~Posion();

	bool StillValid();
	Posion * Clone();
};

