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
	items = new vector<CarryItem*>();
	usingPosions = new vector<CarryItem*>();

	srand(time_t(0));
}

Hero::Hero(string newName, int newLevel, int newLifePoints, int experiancePoints, int newMaxLifePoints, int newAttackPoints, int newAttackChance, int newDefencePoints)
{
	name = newName;
	level = newLevel;
	lifePoints = newLifePoints;
	maxLifePoints = newMaxLifePoints;
	experancePoints = experiancePoints;
	attack = newAttackPoints;
	attackChance = newAttackChance;
	defence = newDefencePoints;
	items = new vector<CarryItem*>();
	usingPosions = new vector<CarryItem*>();

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
	specs->push_back("levens              : " + to_string(TotalLifePoints()));
	specs->push_back("xp                  : " + to_string(experancePoints));
	specs->push_back("aanvals kracht      : " + to_string(TotalAttack()));
	specs->push_back("kans van slagen     : " + to_string(TotalAttackChance()));
	specs->push_back("verdedigings slagen : " + to_string(TotalDefence()));
	specs->push_back("");

	return specs;
}

string Hero::ToStringHealth()
{
	return string("Je hebt nog " + to_string(TotalLifePoints()) + " van de " + to_string(maxLifePoints) + " levenspunten over.");
}

void Hero::MoveTo(Room * movedTo){
	for(auto item : *usingPosions) delete item;
	usingPosions->clear();
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

void Hero::GiveItem(CarryItem * item)
{
	items->push_back(item);
}

bool Hero::DrinkItem(string itemString)
{
	int index = 0;
	for (auto const& item : *items) {
		if(item->GetFunction() == itemString){
			usingPosions->push_back(item);
			items->erase(items->begin() + index);
			return true;
		}
		index++;
	}

	return false;
}

string Hero::GetName()
{
	return name;
}

int Hero::GetPower()
{
	//srand(time_t(0));
	int change = rand() % 100 + 1;

	if (TotalAttackChance() >= change)
		return TotalAttack();

	return 0;
}

int Hero::GetLifePoints()
{
	return TotalLifePoints();
}

int Hero::GetAttackChance()
{
	return TotalAttackChance();
}

bool Hero::TakeDamage(int strength)
{
	//srand(time_t(0));
	int change = rand() % 100 + 1;

	if (TotalDefence() < change) {
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

void Hero::Resting()
{
	lifePoints = maxLifePoints;
}

vector<CarryItem*> Hero::GetPosions()
{
	vector<CarryItem*> poisons = vector<CarryItem*>();

	for (auto const& item : *items)
		if (!item->StillValid())
			poisons.push_back(item);

	return poisons;
}

vector<CarryItem*> Hero::GetObjects()
{
	vector<CarryItem*> objects = vector<CarryItem*>();

	for (auto const& item : *items)
		if (item->StillValid())
			objects.push_back(item);

	return objects;
}

vector<string> Hero::Save()
{
	vector<string> saveLines = vector<string>();

	saveLines.push_back("Name\n");
	saveLines.push_back("["+name+"]\n");

	saveLines.push_back("Level\n");
	saveLines.push_back("[" + to_string(level) + "]\n");

	saveLines.push_back("Experiance\n");
	saveLines.push_back("[" + to_string(experancePoints) + "]\n");

	saveLines.push_back("Life points\n");
	saveLines.push_back("[" + to_string(lifePoints) + "]\n");

	saveLines.push_back("Max life points\n");
	saveLines.push_back("[" + to_string(maxLifePoints) + "]\n");

	saveLines.push_back("Attack points\n");
	saveLines.push_back("[" + to_string(attack) + "]\n");

	saveLines.push_back("Attack chance\n");
	saveLines.push_back("[" + to_string(attackChance) + "]\n");

	saveLines.push_back("Defence chance\n");
	saveLines.push_back("[" + to_string(defence) + "]\n");

	return saveLines;
}

int Hero::TotalAttackChance()
{
	int totalAttackChance = attackChance;

	for (auto const& item : *usingPosions) {
		totalAttackChance += item->AttackChance();
	}

	for (auto const& item : *items) {
		if(item->StillValid())
			totalAttackChance += item->AttackChance();
	}

	return totalAttackChance > 100 ? 100 : totalAttackChance;
}

int Hero::TotalAttack()
{
	int totalAttack = attack;

	for (auto const& item : *usingPosions) {
		totalAttack += item->Attack();
	}

	for (auto const& item : *items) {
		if (item->StillValid())
			totalAttack += item->Attack();
	}

	return totalAttack;
}

int Hero::TotalDefence()
{
	int totalDefence = defence;

	for (auto const& item : *usingPosions) {
		totalDefence += item->DefenceChance();
	}

	for (auto const& item : *items) {
		if (item->StillValid())
			totalDefence += item->DefenceChance();
	}

	return totalDefence > 100 ? 100 : totalDefence;
}

int Hero::TotalLifePoints()
{
	int totalLife = lifePoints;

	for (auto const& item : *usingPosions) {
		totalLife += item->LifePoints();
	}

	for (auto const& item : *items) {
		if (item->StillValid())
			totalLife += item->LifePoints();
	}

	return totalLife;
}
