#include "stdafx.h"

#include "RoomGenerator.h"
#include "EnemyGenerator.h"

#include "FileReader.h"

#include "Game.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <direct.h>
#include <fstream>  
#include <windows.h>

Game::Game()
{
	currentFloor = 0;
	// get input to initialize game
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "--- How do you want to start? ---", "[ new | load | debug ]" });

	bool choice = false;

	while (!choice) {
		string choiceLine = ConsoleReader::getInstance().ReadLine();

		if (choiceLine == "new") {
			SetupCustomPlayer();
			choice = true;
		}

		if (choiceLine == "load") {
			LoadCustomPlayer();
			choice = true;
		}

		if (choiceLine == "debug") {
			SetupDebugPlayer();
			choice = true;
		}
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
	delete dungeon;
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine(new vector<string> { "", "--- A new game will be started ---", ""});
	
	// setup starting location
	int startX = floorDimensionX / 2;
	int startY = floorDimensionY / 2;
 	
	int buildFloor = 0;

	while (buildFloor < 10) {
		dungeon->push_back(RoomGenerator::getInstance().GenerateFloor(startX, startY, buildFloor+1));
		
		//finding room to connect to
		if (buildFloor != 0) {
			bool connected = false;
			while (!connected) {
				startX = rand() % (floorDimensionX - 1);
				startY = rand() % (floorDimensionY - 1);

				if (dungeon->at(buildFloor)[startX][startY] != NULL && dungeon->at(buildFloor-1)[startX][startY] != NULL) {
					dungeon->at(buildFloor)[startX][startY]->ConnectNeighbor(Neighbor::Up, dungeon->at(buildFloor - 1)[startX][startY]);
					dungeon->at(buildFloor - 1)[startX][startY]->ConnectNeighbor(Neighbor::Down, dungeon->at(buildFloor)[startX][startY]);
					connected = true;
				}
			}
		}
		
		buildFloor++;
		if (buildFloor == 10) {
			bool bigGuyPut = false;
			while (!bigGuyPut) {
				startX = rand() % (floorDimensionX - 1);
				startY = rand() % (floorDimensionY - 1);

				if (dungeon->at(9)[startX][startY] != NULL){
					dungeon->at(9)[startX][startY]->SetEndBoss();
					bigGuyPut = true;
				}
			}
		}
	}
	
	//todo find down on current floor
	if (currentFloor == 0) {
		dungeon->at(currentFloor)[floorDimensionX / 2][floorDimensionY / 2]->Enter(player, true);
		player->MoveTo(dungeon->at(currentFloor)[floorDimensionX / 2][floorDimensionY / 2]);
	}
	else {
		for (int x = 0; x < floorDimensionX; x++) {
			for (int y = 0; y < floorDimensionY; y++) {
				if (dungeon->at(currentFloor)[x][y] != NULL && dungeon->at(currentFloor)[x][y]->StartRoomOfFloor()) {
					dungeon->at(currentFloor)[x][y]->Enter(player, false);
					player->MoveTo(dungeon->at(currentFloor)[x][y]);
				}					
			}
		}
	}
	// floor setup

	while (!finished) {
		phase->Run();
	}

	if (player->GetLifePoints() <= 0) {
		ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "HAHAHAHAHHAHAHHAHAA", "Je bent dood....", "", "!!! GAME OVER !!!" });
	}/*word eerder aangegeven
	else {
		ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "JE HEBT GEWONNE!!!!!!!", "Het monster is dood!!", "" });
	}*/

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

void Game::MoveFloor(int level)
{
	currentFloor = currentFloor + level;
}

void Game::PosibleSave()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{"", "--- You want to save the game? ---", "(yes / no)", ""});

	bool saveChoice = false;

	while (!saveChoice) {
		string input = ConsoleReader::getInstance().ReadLine();

		if (input == "no")
			saveChoice = true;

		if (input == "yes") {
			_mkdir("c:/Dungeon Crawler");
			std::ofstream of("C:\\Dungeon Crawler\\" + player->GetName() + ".dun");
			for (auto const& line : player->Save()) {
				of << line;
			}
			of << "floor level\n";
			of << "["+ to_string(currentFloor) +"]\n";

			of << "floor width\n";
			of << "[" + to_string(floorDimensionX) + "]\n";

			of << "floor height\n";
			of << "[" + to_string(floorDimensionY) + "]\n";

			saveChoice = true;
		}
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
	floorRep->push_back("Verdieping: " + to_string(currentFloor + 1));

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
		if (value > 3 && value <= 100)
			floorDimensionX = value;
	}

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Geef de hoogte van de dungeon op:" });
	while (floorDimensionY == 0)
	{
		string input = ConsoleReader::getInstance().ReadLine();
		int value = atoi(input.c_str());
		if (value > 3 && value <= 100)
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

void Game::LoadCustomPlayer()
{
	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Voer de naam van het bestand in dat je wil laden"});

	bool loadChoice = false;
	while (!loadChoice) {

		string fileName = ConsoleReader::getInstance().ReadLine();

		vector<string> * lines = FileReader::getInstance().ReadFile("C:\\Dungeon Crawler\\" + fileName + ".dun", true);

		if (lines->size() > 0) {

			player = new Hero(lines->at(0).substr(1, lines->at(0).size() - 2), ToInt(lines->at(1).substr(1, lines->at(1).size() - 2)), ToInt(lines->at(3).substr(1, lines->at(3).size() - 2)), ToInt(lines->at(2).substr(1, lines->at(2).size() - 2)), ToInt(lines->at(4).substr(1, lines->at(4).size() - 2)), ToInt(lines->at(5).substr(1, lines->at(5).size() - 2)), ToInt(lines->at(6).substr(1, lines->at(6).size() - 2)), ToInt(lines->at(7).substr(1, lines->at(7).size() - 2)));

			currentFloor = ToInt(lines->at(8).substr(1, lines->at(8).size() - 2));
			floorDimensionX = ToInt(lines->at(9).substr(1, lines->at(9).size() - 2));
			floorDimensionY = ToInt(lines->at(10).substr(1, lines->at(10).size() - 2));
		
			loadChoice = true;
		}
		else {
			ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "Probeer opnieuw" });
		}

		delete lines;
	}
}

void Game::SetupDebugPlayer()
{
	floorDimensionX = 4;
	floorDimensionY = 4;

	player = new Hero("Mikes wife");

	ConsoleWriter::getInstance().WriteLine(new vector<string>{ "", "--- Default user en settings made! ---" });
}
