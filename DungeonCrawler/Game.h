#pragma once
#include "Room.h"

class Game
{
	public:
		Game();
		~Game();

		void Play();
	private:
		int floorDimensionX;
		int floorDimensionY;

		void DrawFloor(Room**);
};

