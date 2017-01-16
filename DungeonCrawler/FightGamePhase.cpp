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
	if (player->GetLocation()->AmountOfEnemies() == 0) {
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
				validAction = true;

				const char * cString = action.c_str();
				switch (Str2Int(cString))
				{
				case Str2Int("aanval"):
					FightBeasts();
					break;
				case Str2Int("vlucht"):
					FleeMove();
					break;
				case Str2Int("drink"):
					Drink();
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
		int index = 0;
		for (auto const &enemy : *player->GetLocation()->GetEnemies()) {
			rep->push_back("[" + to_string(index) + "]  " + enemy->ToString());
			index++;
		}
		ConsoleWriter::getInstance().WriteLine(rep);
	}
	else {
		ConsoleWriter::getInstance().WriteLine("Alle beesten zijn gedood.");
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
	if(player->GetPosions().size() > 0)
		actions.push_back("drink");	

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

			//srand(time_t(0));

			//attack a enemy
			ConsoleWriter::getInstance().WriteLine("Je valt " + player->GetLocation()->GetEnemies()->at(value)->GetName() + " aan.");
			
			if (player->GetAttackChance() >= rand() % 100 + 1) {
				int attackpower = player->GetPower();
				if (player->GetLocation()->GetEnemies()->at(value)->TakeDamage(attackpower)) {
					ConsoleWriter::getInstance().WriteLine("Je hebt " + to_string(attackpower) + " schade aangebracht.");
				
					int xp = player->GetLocation()->GetEnemies()->at(value)->DiedGetxp();
					if (xp > 0) {
						if (xp == 999) {
							game->FinishGame();
						}

						player->GiveXp(xp);
						ConsoleWriter::getInstance().WriteLine("Je hebt hem vermoord!");
						delete player->GetLocation()->GetEnemies()->at(value);
						player->GetLocation()->GetEnemies()->erase(player->GetLocation()->GetEnemies()->begin() + value);

						ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "JE HEBT GEWONNE!!!!!!!", "Het monster is dood!!", "" });
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
			vector<string> * enemyAttackLines = new vector<string>{"", "Je tegenstanders deden: "};

			for (auto const &enemy : *player->GetLocation()->GetEnemies()) {
				
				int attackPower = enemy->GetPower();

				string attackPowerLine = "mist";

				if (attackPower > 0)
					if (player->TakeDamage(attackPower))
						attackPowerLine = "doet " + to_string(attackPower) + " schade";
				
				enemyAttackLines->push_back(enemy->GetName()+" bijt en " + attackPowerLine + ".");
			}

			enemyAttackLines->push_back("");
			enemyAttackLines->push_back(player->ToStringHealth());
			enemyAttackLines->push_back("");
			ConsoleWriter::getInstance().WriteLine(enemyAttackLines);

			attacked = true;
		}
	}

	if (player->GetLifePoints() <= 0)
		game->FinishGame();
}

void FightGamePhase::Drink()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Welke pioson wil je drinken?", "" });

	int index = 0;
	for (auto const& item : player->GetPosions()) {
		ConsoleWriter::getInstance().WriteLine("[" + to_string(index) + "]  " + item->GetName() + " : " + item->GetFunction());
		index++;
	}

	bool drunk = false;

	while (!drunk)
	{
		int value = atoi(ConsoleReader::getInstance().ReadLine().c_str());

		if (value >= 0 && value <= player->GetPosions().size() - 1) {
			if(player->DrinkItem(player->GetPosions().at(value)->GetFunction()))
				drunk = true;
		}
	}
}
