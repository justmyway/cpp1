#pragma once

#include "Room.h"
#include "Hero.h"

#include "IGamePhase.h"
#include "InRoomGamePhase.h"

class Game
{
	public:
		Game();
		~Game();

		void Play();
	private:
		int floorDimensionX;
		int floorDimensionY;
		bool finished;
		Room *** floor;
		Hero * player;
		IGamePhase * phase;

		void DrawFloor(Room***);
};

