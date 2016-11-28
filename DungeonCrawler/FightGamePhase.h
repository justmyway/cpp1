#pragma once
#include "IGamePhase.h"
class FightGamePhase :
	public IGamePhase
{
public:
	FightGamePhase(Hero *, Game *);
	~FightGamePhase();
};

