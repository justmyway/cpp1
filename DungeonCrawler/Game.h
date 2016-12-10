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
		void MoveFloor(int);
		void PosibleSave();
		void FinishGame();

		void DrawFloor();
	private:
		int floorDimensionX;
		int floorDimensionY;
		bool finished;

		vector<Room ***> * dungeon;
		int currentFloor;
		Hero * player;
		IGamePhase * phase;

		void SetupCustomPlayer();
		void LoadCustomPlayer();
		void SetupDebugPlayer();
};

