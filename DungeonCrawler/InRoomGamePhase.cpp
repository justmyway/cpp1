#include "stdafx.h"

#include "InRoomGamePhase.h"
#include "RoomPhraseGenerator.h"

#include "Hero.h"
#include "Room.h"
#include "Game.h"

InRoomGamePhase::InRoomGamePhase(Hero * thePlayer, Game * theGame) : IGamePhase(thePlayer, theGame)
{
}


InRoomGamePhase::~InRoomGamePhase()
{
}

void InRoomGamePhase::Run()
{
	DisplayDescription();
	ConsoleWriter::getInstance().WriteLine("");
	DisplayActions();

	bool validAction = false;

	while (!validAction)
	{
		string action = ConsoleReader::getInstance().ReadLine();

		for (auto const& posibility : CreateActions())
		{
			if (posibility.compare(action) == 0) {
				validAction = true;

				const char * cString = action.c_str();
				switch (Str2Int(cString))
				{
				case Str2Int("kaart"):
					game->DrawFloor();
					break;
				default:
					ConsoleWriter::getInstance().WriteLine("System error: on call " + action);
					break;
				}
				//delete cString;
			}
		}

	}
}

void InRoomGamePhase::DisplayDescription()
{
	vector<string> * rep = new vector<string>();

	rep->push_back("Beschrijving: " + *player->GetLocation()->description);
	rep->push_back("");
	rep->push_back("Uitgangen: ");
	for (auto const& neightbor : *player->GetLocation()->MoveOptions()) {
		string exits = "    - ";
		exits += ToString(neightbor);
		exits += " " + RoomPhraseGenerator::getInstance().CreateHallPhrase() + " ";
		rep->push_back(exits);
	}
	rep->push_back("");
	if(player->GetLocation()->AmountOfEnemies() != 0)
		rep->push_back("Aanwezig: ");

	ConsoleWriter::getInstance().WriteLine(rep);
}

void InRoomGamePhase::DisplayActions()
{
	vector<string> * rep = new vector<string>();

	rep->push_back("Wat doe je?");
	rep->push_back("");

	string actionString = "[ ";
	for (auto const &action : CreateActions()) {
		actionString += action;
		if (action.compare(CreateActions().back()) != 0)
			actionString += " | ";
	}
	actionString += " ]";

	rep->push_back(actionString);
	ConsoleWriter::getInstance().WriteLine(rep);
}

vector<string> InRoomGamePhase::CreateActions()
{
	vector<string> actions;

	// do to enemies
	if (player->GetLocation()->AmountOfEnemies() > 0) {
		actions.push_back("vecht");
		actions.push_back("vlucht");
	}
	else {
		actions.push_back("loop");
	}

	// search room
	actions.push_back("zoek");

	// rest if no enemies
	if (player->GetLocation()->AmountOfEnemies() == 0)
		actions.push_back("rust");

	// look at inventory
	actions.push_back("inventaris");

	// look at map
	actions.push_back("kaart");

	return actions;
}