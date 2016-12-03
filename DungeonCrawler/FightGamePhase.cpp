#include "stdafx.h"
#include "FightGamePhase.h"
#include "RoomPhraseGenerator.h"

#include "Hero.h"
#include "Enemy.h"
#include "Room.h"
#include "Game.h"

FightGamePhase::FightGamePhase(Hero * thePlayer, Game * theGame) : IGamePhase(thePlayer, theGame)
{
}


FightGamePhase::~FightGamePhase()
{
}

void FightGamePhase::Run()
{
	DisplayDescription();

	if (player->GetLocation()->AmountOfEnemies() == 0) {
		game->SetPhase("InRoom");
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
				case Str2Int("vlucht"):
					FleeMove();
					break;
				default:
					ConsoleWriter::getInstance().WriteLine("System error: on call " + action);
					break;
				}
			}
		}

	}
}

void FightGamePhase::DisplayDescription()
{
	if (player->GetLocation()->AmountOfEnemies() != 0) {
		vector<string> * rep = new vector<string>();

		rep->push_back("Aanwezig: ");
		vector<Enemy*>::iterator it;
		int index = 0;
		for (it = player->GetLocation()->GetEnemies()->begin(); it != player->GetLocation()->GetEnemies()->end(); ++it) {
			rep->push_back("["+to_string(index)+"]  "+(*it)->ToString());
			index++;
		}
		ConsoleWriter::getInstance().WriteLine(rep);
	}
	else {
		ConsoleWriter::getInstance().WriteLine("Alle beesten zijn gedood");
	}
}

void FightGamePhase::DisplayActions()
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

vector<string> FightGamePhase::CreateActions()
{
	vector<string> actions;

	// do to enemies
	actions.push_back("aanval");
	actions.push_back("vlucht");

	// drankje drinken
	if(player->GetPosions()->size() > 0)
		actions.push_back("drink");

	if (player->GetObjects()->size() > 0)
		actions.push_back("gebruik");	

	return actions;
}

void FightGamePhase::FleeMove()
{
	ConsoleWriter::getInstance().WriteLine("Uitgangen: ");
	for (auto const& neightbor : *player->GetLocation()->MoveOptions()) {
		string exits = "    - ";
		exits += ToString(neightbor);
		exits += " " + RoomPhraseGenerator::getInstance().CreateHallPhrase() + " ";
		ConsoleWriter::getInstance().WriteLine(exits);
	}
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Welke kant wil je op vluchten? (n, e, s, w)", "" });

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

		for (auto const &action : *player->GetLocation()->MoveOptions()) {
			if (Str2Int(input.c_str()) == Str2Int(ToString(action))) {
				player->GetLocation()->MoveTo(action);
				moved = true;
			}
		}
	}
}

void FightGamePhase::FightBeasts()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Welke beest wil je aanvallen?", "" });

	bool attacked = false;

	while (!attacked)
	{
		int value = atoi(ConsoleReader::getInstance().ReadLine().c_str());

		if (value >= 0 && value <= player->GetLocation()->GetEnemies()->size() -1) {

			srand(time_t(0));

			//attack a enemy
			ConsoleWriter::getInstance().WriteLine("Je valt " + player->GetLocation()->GetEnemies()->at(value)->GetName() + " aan.");
			
			if (player->GetAttackChance() >= rand() % 100 + 1) {
				int attackpower = player->GetPower();
				if (player->GetLocation()->GetEnemies()->at(value)->TakeDamage(attackpower)) {
					ConsoleWriter::getInstance().WriteLine("Je hebt " + to_string(attackpower) + " schade aangebracht.");
				
					int xp = player->GetLocation()->GetEnemies()->at(value)->DiedGetxp();
					if (xp > 0) {
						ConsoleWriter::getInstance().WriteLine("Je hebt hem vermoord!");
					}
				}
				else {
					ConsoleWriter::getInstance().WriteLine("De " + player->GetLocation()->GetEnemies()->at(value)->GetName() + " ontwijkt je aanval");
				}
			}
			else {
				ConsoleWriter::getInstance().WriteLine("Je moet wel raak slaan. HAHAHAAHHAH");
			}

			//enemies attacking

			attacked = true;
		}

		for (auto const &action : *player->GetLocation()->MoveOptions()) {
			if (Str2Int(input.c_str()) == Str2Int(ToString(action))) {
				player->GetLocation()->MoveTo(action);
				attacked = true;
			}
		}
	}
}
