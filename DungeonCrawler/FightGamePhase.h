#pragma once
#include "IGamePhase.h"

class FightGamePhase :
	public IGamePhase
{
public:
	FightGamePhase(Hero*, Game*);
	~FightGamePhase();

	void Run();

private:
	void DisplayDescription();
	void DisplayActions();
	vector<string> CreateActions();

	void FleeMove();
	void FightBeasts();
};

