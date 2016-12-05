#pragma once

#include "Room.h"
#include "Hero.h"

#include "IGamePhase.h"
#include "InRoomGamePhase.h"
#include "FightGamePhase.h"
#include "LevelUpGamePhase.h"

class Game
{
	public:
		Game();
		~Game();

		void Play();
		void SetPhase(string);
		void FinishGame();

		void DrawFloor();
	private:
		int floorDimensionX;
		int floorDimensionY;
		bool finished;

		bool debug = true;

		vector<Room ***> * dungeon;
		int currentFloor;
		Hero * player;
		IGamePhase * phase;

		void SetupCustomPlayer();
		void SetupDebugPlayer();
};

