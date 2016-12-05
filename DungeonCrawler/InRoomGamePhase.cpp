#include "stdafx.h"

#include "InRoomGamePhase.h"
#include "RoomPhraseGenerator.h"

#include "Hero.h"
#include "Enemy.h"
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
	if (player->GetLocation()->AmountOfEnemies() > 0) {
		game->SetPhase("Fight");
		return;
	}
	if (player->CanLevelUp()) {
		game->SetPhase("LevelUp");
		return;
	}
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
				case Str2Int("loop"):
					WalkMove();
					break;
				case Str2Int("rust"):
					Resting();
					break;
				case Str2Int("kaart"):
					game->DrawFloor();
					break;
				case Str2Int("speler"):
					ConsoleWriter::getInstance().WriteLine(player->ToString());
					break;
				default:
					ConsoleWriter::getInstance().WriteLine("System error: on call " + action);
					break;
				}
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

	// look at map
	actions.push_back("speler");

	return actions;
}

void InRoomGamePhase::WalkMove()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Welke kant wil je op? (n, e, s, w, u, d)", "Mogelijke zetten zijn hier boven weergegeven" , "" });

	bool moved = false;

	while (!moved)
	{
		string input = ConsoleReader::getInstance().ReadLine();

		if (Str2Int(input.c_str()) == Str2Int("n")) {
			input = "North";
		}

		if (Str2Int(input.c_str()) == Str2Int("e")) {
			input = "East";
		}

		if (Str2Int(input.c_str()) == Str2Int("s")) {
			input = "South";
		}

		if (Str2Int(input.c_str()) == Str2Int("w")) {
			input = "West";
		}

		if (Str2Int(input.c_str()) == Str2Int("u")) {
			input = "Up";
		}

		if (Str2Int(input.c_str()) == Str2Int("d")) {
			input = "Down";
		}

		for (auto const &action : *player->GetLocation()->MoveOptions()) {
			if (Str2Int(input.c_str()) == Str2Int(ToString(action))) {
				player->GetLocation()->MoveTo(action);
				if (Str2Int(input.c_str()) == Str2Int("Down")) {
					game->MoveFloor(1);
				} 
				if (Str2Int(input.c_str()) == Str2Int("Up")) {
					game->MoveFloor(-1);
				}
				moved = true;
			}
		}
	}
}

void InRoomGamePhase::Resting()
{
	ConsoleWriter::getInstance().WriteLine("Zow even een tukky, hopen dat ik niet word aan gevallen!");

	player->Resting();

	int chance = rand() % 100;
	if (chance < 50) {
		player->GetLocation()->GenEnemies();
		ConsoleWriter::getInstance().WriteLine("Verdomme tijdens het rusten zijn er monsters langs gekomen en vallen ze aan!");
	}
	else {
		ConsoleWriter::getInstance().WriteLine("Dat was een lekker tukky");
	}
}
