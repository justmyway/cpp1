#include "stdafx.h"

#include "RoomGenerator.h"
#include "EnemyGenerator.h"

#include "Game.h"

#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
	// get input to initialize game
	if (debug) {
		SetupDebugPlayer();
	} else {
		SetupCustomPlayer();
	}

	finished = false;

	RoomGenerator::getInstance().setFloorDimensions(floorDimensionX, floorDimensionY);
	SetPhase("InRoom");

	dungeon = new vector<Room ***>();
}


Game::~Game()
{
	delete player;
	delete phase;
	delete dungeon
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine(new vector<string> { "", "--- A new game will be started ---", ""});
	
	// setup starting location
	int startX = floorDimensionX / 2;
	int startY = floorDimensionY / 2;
 	
	int buildFloor = 0;

	while (buildFloor < 10) {
		dungeon->push_back(RoomGenerator::getInstance().GenerateFloor(startX, startY));
		buildFloor++;
		if (buildFloor < 10) {
			//random pick on floor
		}
	}
	
	currentFloor = 0;
	dungeon->at(currentFloor)[startX][startY]->Enter(player);
	player->MoveTo(dungeon->at(currentFloor)[startX][startY]);
	// floor setup

	while (!finished) {
		phase->Run();
	}

	if (player->GetLifePoints() <= 0)
		ConsoleWriter::getInstance().WriteLine(new vector<string>{"", "HAHAHAHAHHAHAHHAHAA", "Je bent dood....", "", "!!! GAME OVER !!!"});

	system("PAUSE");

	//remove whole dungeon
	while (dungeon->size() != 0) {
		Room *** floor = dungeon->back();
		dungeon->pop_back();

		for (int i = floorDimensionX - 1; i >= 0; i--)
		{
			for (int j = floorDimensionY - 1; j >= 0; j--)
				delete floor[i][j];

			delete[] floor[i];
		}
		delete[] floor;
	}
}

void Game::SetPhase(string newPhase)
{
	delete phase;

	if (newPhase == "InRoom") {
		phase = new InRoomGamePhase(player, this);
	}else if (newPhase == "Fight") {
		phase = new FightGamePhase(player, this);
	}	else if (newPhase == "LevelUp") { 
		phase = new LevelUpGamePhase(player, this);
	}
	else {
		ConsoleWriter::getInstance().WriteLine("Phase not recognised");
		exit(EXIT_FAILURE);
	}
}

void Game::FinishGame()
{
	finished = true;
}

void Game::DrawFloor() {

	Room *** floor = dungeon->at(currentFloor);

	vector<string> * floorRep = new vector<string>();

	floorRep->push_back("");
	floorRep->push_back("Verdieping: ");

	for (int y = floorDimensionY - 1; y >= 0; y--) {
		
		string floorLine = "  ";
		for (int x = 0; x < floorDimensionX; x++) {
			if (floor[x][y] != NULL) {
				floorLine += floor[x][y]->ToString();
			}
			else {
				floorLine += ".  ";
			}
		}

		floorRep->push_back(floorLine);

		if (y != 0) {
			floorLine = "  ";
			for (int x = 0; x < floorDimensionX; x++) {
				if (floor[x][y] != NULL) {
					floorLine += floor[x][y]->ToStringSouthCoridor();
				}
				else {
					floorLine += "   ";
				}
			}
			floorRep->push_back(floorLine);
		}
	}

	floorRep->push_back("Legenda:");
	floorRep->push_back("|- : Gangen");
	floorRep->push_back("S  : Start locatie");
	floorRep->push_back("E  : Eind vijand");
	floorRep->push_back("N  : Normale ruimte");
	floorRep->push_back("L  : Trap omlaag");
	floorRep->push_back("H  : Trap omhoog");
	floorRep->push_back(".  : Niet bezocht");
	floorRep->push_back("");

	ConsoleWriter::getInstance().WriteLine(floorRep);

	delete floor;
}

void Game::SetupCustomPlayer()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "--- Setup the game ---", "" });

	ConsoleWriter::getInstance().WriteLine("Geef de breedte van de dungeon op:");
	while (floorDimensionX == 0)
	{
		string input = ConsoleReader::getInstance().ReadLine();
		int value = atoi(input.c_str());
		if (value > 4 && value <= 100)
			floorDimensionX = value;
	}

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Geef de hoogte van de dungeon op:" });
	while (floorDimensionY == 0)
	{
		string input = ConsoleReader::getInstance().ReadLine();
		int value = atoi(input.c_str());
		if (value > 4 && value <= 100)
			floorDimensionY = value;
	}

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Wat is de naam van jou Hero?:" });
	string name;
	while (Str2Int(name.c_str()) == Str2Int(""))
	{
		name = ConsoleReader::getInstance().ReadLine();
	}

	player = new Hero(name);
}

void Game::SetupDebugPlayer()
{
	floorDimensionX = 8;
	floorDimensionY = 8;

	player = new Hero("Mikes wife");

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "--- Default user en settings made! ---" });
}
