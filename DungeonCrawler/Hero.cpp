#include "stdafx.h"
#include "Hero.h"


Hero::Hero(string newName)
{
	name = newName;
	level = 1;
	lifePoints = 10;
	experancePoints = 0;
	attack = 2;
	defence = 2;
	items = new vector<CarryItem>();
}


Hero::~Hero()
{
	delete items;
}

void Hero::MoveTo(Room * movedTo) {
	room = movedTo;
}

Room * Hero::GetLocation()
{
	return room;
}
