#pragma once
#include "IGamePhase.h"

class LevelUpGamePhase :
	public IGamePhase
{
public:
	LevelUpGamePhase(Hero*, Game*);
	~LevelUpGamePhase();

	void Run();

private:
	void DisplayDescription();
	void DisplayActions();
	vector<string> CreateActions();
};

