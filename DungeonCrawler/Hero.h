#pragma once

#include "CarryItem.h"

class Room;

class Hero
{
	public:
		Hero(string);
		~Hero();

		vector<string> * ToString();
		string ToStringHealth();
		void MoveTo(Room *);
		Room * GetLocation();
		
		void GiveXp(int);
		void GiveItem(CarryItem*);
		bool DrinkItem(string);
		int GetPower();
		int GetLifePoints();
		int GetAttackChance();
		bool TakeDamage(int);
		bool CanLevelUp();
		bool UpGrade(string);
		void Resting();
		vector<CarryItem*> GetPosions();
		vector<CarryItem*> GetObjects();

	private:
		string name;
		int level;
		int needToLevel = 0;
		int experancePoints;
		int lifePoints;
		int maxLifePoints;
		int attack;
		int attackChance;
		int defence;

		vector<CarryItem*> * items;
		vector<CarryItem*> * usingPosions;
		Room * room;

		int TotalAttackChance();
		int TotalAttack();
		int TotalDefence();
		int TotalLifePoints();
};

