#include "stdafx.h"
#include "Armour.h"


Armour::Armour(string n, string f, int l, int a, int ac, int dc) : CarryItem(n, f, l, a, ac, dc)
{
}

Armour::~Armour()
{
}

bool Armour::StillValid()
{
	return true;
}

Armour * Armour::Clone()
{
	return new Armour(name, function, lifePoints, attack, attackChance, defenceChance);
}
