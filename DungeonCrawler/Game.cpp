#include "stdafx.h"

#include "RoomGenerator.h"

#include "Game.h"

#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
	floorDimensionX = 60;
	floorDimensionY = 30;
	RoomGenerator::getInstance().setFloorDimensions(floorDimensionX, floorDimensionY);

	player = new Hero();
}


Game::~Game()
{
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine("A new game will be started");
 	//for (int i = 0; i < 2; i++) {
		floor = RoomGenerator::getInstance().GenerateFloor(30, 15);
		floor = RoomGenerator::getInstance().GenerateFloor(30, 15);

		floor[30][15]->Enter(player);
		player->MoveTo(floor[30][15]);

		for (int i = 0; i < 100; i++) {
			//draw floor
			ConsoleWriter::getInstance().ClearView();
			DrawFloor(floor);

			for (auto const& neightbor : *player->GetLocation()->MoveOptions()) {
				ConsoleWriter::getInstance().WriteLine(ToString(neightbor));
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
			
		}

		/*for (int i = floorDimensionX -1; i >= 0; i--)
		{
			for (int j = floorDimensionY - 1; j >= 0; j--) 
				delete floor[i][j];

			delete[] floor[i];
		}
		delete[] floor;*/
	//}
}

void Game::DrawFloor(Room *** floor) {
	ConsoleWriter::getInstance().WriteLine("Floor:");

	for (int y = floorDimensionY - 1; y >= 0; y--) {
		
		string floorLine = " ";
		for (int x = 0; x < floorDimensionX; x++) {
			if (floor[x][y] != NULL) {
				floorLine += floor[x][y]->ToString();
			}
			else {
				floorLine += ".  ";
			}
		}

		ConsoleWriter::getInstance().WriteLine(floorLine);

		if (y != 0) {
			floorLine = " ";
			for (int x = 0; x < floorDimensionX; x++) {
				if (floor[x][y] != NULL) {
					floorLine += floor[x][y]->ToStringSouthCoridor();
				}
				else {
					floorLine += "   ";
				}
			}
			ConsoleWriter::getInstance().WriteLine(floorLine);
		}
	}

	/*for (int x = floorDimensionX - 1; x >= 0; x--) {
		
		string floorLine = " ";
		for (int y = 0; y < floorDimensionY; y++) {
			if (floor[x][y] != NULL) {
				floorLine += floor[x][y]->ToString();
			} else {
				floorLine += ".  ";
			}
		}
		ConsoleWriter::getInstance().WriteLine(floorLine);

		if (x != 0) {
			floorLine = " ";
			for (int y = 0; y < floorDimensionY; y++) {
				if (floor[x][y] != NULL) {
					floorLine += floor[x][y]->ToStringSouthCoridor();
				} else {
					floorLine += "   ";
				}
			}
			ConsoleWriter::getInstance().WriteLine(floorLine);
		}
	}
	ConsoleWriter::getInstance().WriteLine("");*/
}