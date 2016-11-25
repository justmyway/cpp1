#include "stdafx.h"
#include "Game.h"

#include "RoomGenerator.h"

Game::Game()
{
	floorDimensionX = 15;
	floorDimensionY = 15;
	RoomGenerator::getInstance().setFloorDimensions(floorDimensionX, floorDimensionY);
}


Game::~Game()
{
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine("A new game will be started");
 	for (int i = 0; i < 10; i++) {
		Room *** floor = RoomGenerator::getInstance().GenerateFloor(5, 5);

		//draw floor
		DrawFloor(floor);
		for (int i = floorDimensionX -1; i >= 0; i--)
		{
			for (int j = floorDimensionY - 1; j >= 0; j--) 
				delete floor[i][j];

			delete[] floor[i];
		}
		delete[] floor;
	}
}

void Game::DrawFloor(Room *** floor) {
	ConsoleWriter::getInstance().WriteLine("Floor:");

	for (int x = floorDimensionX - 1; x >= 0; x--) {
		
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
	ConsoleWriter::getInstance().WriteLine("");
}