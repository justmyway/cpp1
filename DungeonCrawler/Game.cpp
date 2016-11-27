#include "stdafx.h"

#include "RoomGenerator.h"

#include "Game.h"

#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
	floorDimensionX = 10;
	floorDimensionY = 10;
	finished = false;

	RoomGenerator::getInstance().setFloorDimensions(floorDimensionX, floorDimensionY);

	player = new Hero();
	phase = new InRoomGamePhase();
}


Game::~Game()
{
	delete player;
	delete phase;
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine("A new game will be started");

	// setup starting location
	int startX = floorDimensionX / 2;
	int startY = floorDimensionY / 2;
 	
	floor = RoomGenerator::getInstance().GenerateFloor(startX, startY);
	floor = RoomGenerator::getInstance().GenerateFloor(startX, startY);
	
	floor[startX][startY]->Enter(player);
	player->MoveTo(floor[startX][startY]);
	// floor setup


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

void Game::DrawFloor(Room *** floor) {
	ConsoleWriter::getInstance().WriteLine("Floor:");

	vector<string> * floorRep = new vector<string>();

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

	ConsoleWriter::getInstance().WriteLine(floorRep);
}