#pragma once

#include "CarryItem.h"

class Room;

class Hero
{
	public:
		Hero(string);
		~Hero();

		vector<string> * ToString();
		void MoveTo(Room *);
		Room * GetLocation();
		
		void GiveXp(int);
		int GetPower();
		int GetAttackChance();
		vector<string> * GetPosions();
		vector<string> * GetObjects();

	private:
		string name;
		int level;
		int experancePoints;
		int lifePoints;
		int attack;
		int attackChance;
		int defence;

		vector<CarryItem> * items;
		Room * room;
};

