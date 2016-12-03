#include "stdafx.h"
#include "Hero.h"


Hero::Hero(string newName)
{
	name = newName;
	level = 1;
	lifePoints = 10;
	experancePoints = 0;
	attack = 2;
	attackChance = 20;
	defence = 2;
	items = new vector<CarryItem>();
}


Hero::~Hero()
{
	delete items;
}

vector<string> * Hero::ToString()
{
	vector<string> * specs = new vector<string>();

	specs->push_back("De eigenschappen van " + name + " : ");
	specs->push_back("level	             : " + to_string(level));
	specs->push_back("levens              : " + to_string(lifePoints));
	specs->push_back("aanvals kracht      : " + to_string(attack));
	specs->push_back("kans van slagen     : " + to_string(attackChance));
	specs->push_back("verdedigings kracht : " + to_string(defence));
	specs->push_back("");

	return specs;
}

void Hero::MoveTo(Room * movedTo) {
	room = movedTo;
}

Room * Hero::GetLocation()
{
	return room;
}

void Hero::GiveXp(int points)
{
	experancePoints += points;

	//todo

	//level up regelen
}

int Hero::GetPower()
{
	srand(time_t(0));
	int change = rand() % 100 + 1;

	if (attackChance >= change)
		return attack;

	return 0;
}

int Hero::GetAttackChance()
{
	return attackChance;
}

vector<string>* Hero::GetPosions()
{
	return new vector<string>();
}

vector<string>* Hero::GetObjects()
{
	return new vector<string>();
}
