#pragma once

#include "Room.h"
#include "Hero.h"

#include "IGamePhase.h"
#include "InRoomGamePhase.h"
#include "FightGamePhase.h"

class Game
{
	public:
		Game();
		~Game();

		void Play();
		void SetPhase(string);

		void DrawFloor();
	private:
		int floorDimensionX;
		int floorDimensionY;
		bool finished;

		bool debug = true;

		Room *** floor;
		Hero * player;
		IGamePhase * phase;

		void SetupCustomPlayer();
		void SetupDebugPlayer();
};

