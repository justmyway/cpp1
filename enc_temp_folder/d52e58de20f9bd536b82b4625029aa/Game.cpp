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
	Room *** floor = RoomGenerator::getInstance().GenerateFloor(1, 1);

	//draw floor
	DrawFloor(floor);
}

void Game::DrawFloor(Room *** floor) {
	ConsoleWriter::getInstance().WriteLine("Floor:");

	for (int x = floorDimensionX - 1; x >= 0; x--) {
		
		string floorLine = "";
		for (int y = 0; y < floorDimensionY; y++) {
			floorLine += floor[x][y]->ToString();
		}
		ConsoleWriter::getInstance().WriteLine(floorLine);

		if (x =! floorDimensionX - 1) {
			floorLine = "";
			for (int y = 0; y < floorDimensionY; y++) {
				floorLine += floor[x][y]->ToStringSouthCoridor();
			}
			ConsoleWriter::getInstance().WriteLine(floorLine);
		}
	}
}