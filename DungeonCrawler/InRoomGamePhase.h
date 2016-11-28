#pragma once
#include "IGamePhase.h"

class InRoomGamePhase :
	public IGamePhase
{
	public:
		InRoomGamePhase(Hero *, Game *);
		~InRoomGamePhase();

		void Run();

	private:
		void DisplayDescription();
		void DisplayActions();
		vector<string> CreateActions();
};

