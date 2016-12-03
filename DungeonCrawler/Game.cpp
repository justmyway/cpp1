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
}


Game::~Game()
{
	delete player;
	delete phase;
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine(new vector<string> { "", "--- A new game will be started ---", ""});
	
	// setup starting location
	int startX = floorDimensionX / 2;
	int startY = floorDimensionY / 2;
 	
	floor = RoomGenerator::getInstance().GenerateFloor(startX, startY);
	floor = RoomGenerator::getInstance().GenerateFloor(startX, startY);
	
	floor[startX][startY]->Enter(player);
	player->MoveTo(floor[startX][startY]);
	// floor setup

	//EnemyGenerator::getInstance().GenerateEnemy(1);

	while (!finished) {
		phase->Run();
	}
	
	
	////for (int i = 0; i < 2; i++) {
	//	floor = RoomGenerator::getInstance().GenerateFloor(35, 13);
	//	floor = RoomGenerator::getInstance().GenerateFloor(35, 13);

	//	floor[35][13]->Enter(player);
	//	player->MoveTo(floor[35][13]);

	//	int x = 0;

	//	for (int i = 0; i < 100000; i++) {
	//		//if (x = 1000) {
	//			//draw floor
	//			ConsoleWriter::getInstance().ClearView();
	//			DrawFloor(floor);
	//			x = 0;
	//		//}

	//		vector<Neighbor> posibleNeightbors = *player->GetLocation()->MoveOptions();

	//		for (auto const& neightbor : posibleNeightbors) {
	//			ConsoleWriter::getInstance().WriteLine(ToString(neightbor));
	//		}

	//		Neighbor directionToMoveTo = posibleNeightbors.at(rand() % posibleNeightbors.size());

	//		ConsoleWriter::getInstance().WriteLine("Will move to -> " + string(ToString(directionToMoveTo)));

	//		player->GetLocation()->MoveTo(directionToMoveTo);

	//		//std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//		
	//	}

	//	/*for (int i = floorDimensionX -1; i >= 0; i--)
	//	{
	//		for (int j = floorDimensionY - 1; j >= 0; j--) 
	//			delete floor[i][j];

	//		delete[] floor[i];
	//	}
	//	delete[] floor;*/
	////}
}

void Game::SetPhase(string newPhase)
{
	delete phase;

	if (newPhase == "InRoom") {
		phase = new InRoomGamePhase(player, this);
	}else if (newPhase == "Fight") {
		phase = new FightGamePhase(player, this);
	}
	else {
		ConsoleWriter::getInstance().WriteLine("Phase not recognised");
		exit(EXIT_FAILURE);
	}
}

void Game::DrawFloor() {
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
	floorDimensionX = 12;
	floorDimensionY = 12;

	player = new Hero("Mikes wife");

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "--- Default user en settings made! ---" });
}
