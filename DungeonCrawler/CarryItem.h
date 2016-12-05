#pragma once
class CarryItem
{
public:
	CarryItem(string, string, int, int, int, int);
	~CarryItem();

	string GetName();
	string GetFunction();

	virtual bool StillValid() = 0;
	virtual CarryItem * Clone() = 0;
	int LifePoints();
	int Attack();
	int AttackChance();
	int DefenceChance();


protected:
	string name;
	string function;

	int lifePoints;
	int attack;
	int attackChance;
	int defenceChance;
};

