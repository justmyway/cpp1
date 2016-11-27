#pragma once

//#include "Hero.h"

class Hero;
class Room;

class IGamePhase
{
	public:
		IGamePhase();
		~IGamePhase();

		virtual void Run() = 0;

	protected:
		Hero * player;
};

