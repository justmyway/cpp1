#pragma once
#include "IGamePhase.h"

class InRoomGamePhase :
	public IGamePhase
{
	public:
		InRoomGamePhase(Hero *);
		~InRoomGamePhase();

		void Run();

	private:
		void DisplayDescription();
		void DisplayActions();
};

