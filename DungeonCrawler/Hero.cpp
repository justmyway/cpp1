#include "stdafx.h"
#include "Hero.h"


Hero::Hero()
{
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
