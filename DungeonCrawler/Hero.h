#pragma once

#include "CarryItem.h"

class Hero
{
public:
	string name;
	int level;
	int experancePoints;
	int lifePoints;
	int attack;
	int defence;

	vector<CarryItem> *items;

	Hero();
	~Hero();
};

