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