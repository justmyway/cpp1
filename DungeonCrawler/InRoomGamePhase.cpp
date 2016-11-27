#include "stdafx.h"
#include "InRoomGamePhase.h"


InRoomGamePhase::InRoomGamePhase(Hero * thePlayer)
{
	player = thePlayer;
}


InRoomGamePhase::~InRoomGamePhase()
{
}

void InRoomGamePhase::Run()
{

}

void InRoomGamePhase::DisplayDescription()
{
	vector<string> * rep = new vector<string>();

	player->GetLocation()->description;


	rep->push_back("Beschrijving: " + player->GetLocation()->description);

	ConsoleWriter::getInstance().WriteLine(rep);
}

void InRoomGamePhase::DisplayActions()
{
}
