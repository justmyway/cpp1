#include "stdafx.h"
#include "RoomGenerator.h"

#include "RoomPhraseGenerator.h"

RoomGenerator::RoomGenerator()
{
}

RoomGenerator & RoomGenerator::getInstance() {
	static RoomGenerator instance;
	return instance;
}

void RoomGenerator::setFloorDimensions(const int width, const int height) {
	roomWidthFloor = width;
	roomHeightFloor = height;
}

Room * RoomGenerator::GenerateFloor(int beginX, int beginY) {

	Room*** floor;
	floor[beginX][beginY] = new Room();

	//create floor
	CreateNeighbors(floor[beginX][beginY], beginX, beginY, 1);
	
	for (int i = 0; i < 10000; i++) {
		ConsoleWriter::getInstance().WriteLine(*RoomPhraseGenerator::getInstance().CreateRoomPhrase());
	}
	return new Room();
}

void RoomGenerator::CreateNeighbors(Room* room, int x, int y, int amountOfRooms) {
	
}