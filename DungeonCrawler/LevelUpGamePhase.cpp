#include "stdafx.h"
#include "LevelUpGamePhase.h"

#include "Hero.h"
#include "Game.h"

LevelUpGamePhase::LevelUpGamePhase(Hero * thePlayer, Game * theGame) : IGamePhase(thePlayer, theGame)
{
}

LevelUpGamePhase::~LevelUpGamePhase()
{
}

void LevelUpGamePhase::Run()
{
	if (!player->CanLevelUp()) {
		game->SetPhase("InRoom");
		return;
	}

	DisplayDescription();

	DisplayActions();

	bool validAction = false;

	while (!validAction)
	{
		string action = ConsoleReader::getInstance().ReadLine();

		for (auto const& posibility : CreateActions())
		{
			if (posibility.compare(action) == 0) {
				if (player->UpGrade(action)) {
					validAction = true;
				}
				else {
					ConsoleWriter::getInstance().WriteLine("Deze skill: " + action + " kon niet worden geupgrade, kies een andere.");
				}
			}
		}

	}
}

void LevelUpGamePhase::DisplayDescription()
{
	ConsoleWriter::getInstance().WriteLine("Het is zo ver je mag een level omhoog!!!");
}

void LevelUpGamePhase::DisplayActions()
{
	vector<string> * rep = new vector<string>();
	rep->push_back("Je mag nu een skill verbeteren, hier onder kun je kiezen welke:");
	rep->push_back("");

	for (auto const &action : CreateActions()) {
		rep->push_back("   - " + action);
	}

	ConsoleWriter::getInstance().WriteLine(rep);
}

vector<string> LevelUpGamePhase::CreateActions()
{
	vector<string> actions;

	actions.push_back("levens");
	actions.push_back("aanvals-kracht");
	actions.push_back("aanvals-kans");
	actions.push_back("verdedigings-kans");

	return actions;
}
