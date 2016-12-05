#include "stdafx.h"
#include "CarryItem.h"


CarryItem::CarryItem(string n, string f, int l, int a, int ac, int dc) : name(n), function(f), lifePoints(l), attack(a), attackChance(ac), defenceChance(dc)
{
}

CarryItem::~CarryItem()
{
}

string CarryItem::GetName()
{
	return name;
}

string CarryItem::GetFunction()
{
	return function;
}

int CarryItem::LifePoints()
{
	return lifePoints;
}

int CarryItem::Attack()
{
	return attack;
}

int CarryItem::AttackChance()
{
	return attackChance;
}

int CarryItem::DefenceChance()
{
	return defenceChance;
}
