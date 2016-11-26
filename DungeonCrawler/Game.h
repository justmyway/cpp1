#pragma once

#include "Room.h"
#include "Hero.h"

class Game
{
	public:
		Game();
		~Game();

		void Play();
	private:
		int floorDimensionX;
		int floorDimensionY;
		Room *** floor;
		Hero * player;

		void DrawFloor(Room***);
};

