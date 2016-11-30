#pragma once

#include "CarryItem.h"

class Room;

class Hero
{
	public:
		Hero(string);
		~Hero();

		void MoveTo(Room *);
		Room * GetLocation();

	private:
		string name;
		int level;
		int experancePoints;
		int lifePoints;
		int attack;
		int defence;

		vector<CarryItem> * items;
		Room * room;
};

