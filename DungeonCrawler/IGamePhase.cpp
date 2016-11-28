#include "stdafx.h"
#include "IGamePhase.h"


IGamePhase::IGamePhase(Hero * thePlayer, Game * theGame)
{
	player = thePlayer;
	game = theGame;
}


IGamePhase::~IGamePhase()
{
}
