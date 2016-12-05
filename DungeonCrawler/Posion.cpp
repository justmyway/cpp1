#include "stdafx.h"
#include "Posion.h"


Posion::Posion(string n, string f, int l, int a, int ac, int dc) : CarryItem(n, f, l, a, ac, dc)
{
}


Posion::~Posion()
{
}

bool Posion::StillValid()
{
	return false;
}

Posion * Posion::Clone()
{
	return new Posion(name, function, lifePoints, attack, attackChance, defenceChance);
}
