#include "stdafx.h"
#include "Hero.h"


Hero::Hero(string newName)
{
	name = newName;
	level = 1;
	lifePoints = 10;
	maxLifePoints = 10;
	experancePoints = 0;
	attack = 2;
	attackChance = 40;
	defence = 40;
	items = new vector<CarryItem>();

	srand(time_t(0));
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
	specs->push_back("xp                  : " + to_string(experancePoints));
	specs->push_back("aanvals kracht      : " + to_string(attack));
	specs->push_back("kans van slagen     : " + to_string(attackChance));
	specs->push_back("verdedigings slagen : " + to_string(defence));
	specs->push_back("");

	return specs;
}

string Hero::ToStringHealth()
{
	return string("Je hebt nog " + to_string(lifePoints) + " van de " + to_string(maxLifePoints) + " levenspunten over.");
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

	int totalLevel = level + needToLevel;

	if (experancePoints >= 25*totalLevel*(1+totalLevel))
		needToLevel++;
}

int Hero::GetPower()
{
	//srand(time_t(0));
	int change = rand() % 100 + 1;

	if (attackChance >= change)
		return attack;

	return 0;
}

int Hero::GetLifePoints()
{
	return lifePoints;
}

int Hero::GetAttackChance()
{
	return attackChance;
}

bool Hero::TakeDamage(int strength)
{
	//srand(time_t(0));
	int change = rand() % 100 + 1;

	if (defence < change) {
		lifePoints -= strength;
		return true;
	}

	return false;
}

bool Hero::CanLevelUp()
{
	return needToLevel > 0;
}

bool Hero::UpGrade(string value)
{
	if (value == "levens") {
		maxLifePoints = (maxLifePoints + 10) * 1.2;
	}
	else if(value == "aanvals-kracht"){
		attack = (attack + 4) * 1.8;
	}
	else if (value == "aanvals-kans") {
		if (attackChance >= 100)
			return false;

		attackChance = (attackChance * 1.5) + 20;

		if (attackChance > 100)
			attackChance = 100;
	}
	else if (value == "verdedigings-kans") {
		if (defence >= 100)
			return false;

		defence += 20;

		if (defence > 100)
			defence = 100;
	}
	else {
		return false;
	}

	needToLevel--;
	level++;

	return true;
}

vector<string>* Hero::GetPosions()
{
	return new vector<string>();
}

vector<string>* Hero::GetObjects()
{
	return new vector<string>();
}
