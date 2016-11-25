#pragma once

#include "CarryItem.h"
#include "Room.h"

class Hero
{
	public:
		Hero();
		~Hero();

		string name;
		int level;
		int experancePoints;
		int lifePoints;
		int attack;
		int defence;

		vector<CarryItem> *items;

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

