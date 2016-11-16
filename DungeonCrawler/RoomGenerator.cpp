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
	// determ max rooms to create: first has 4 posibilities
	unsigned int maxRoomsToCreate = (amountOfRooms == 1 ? 4 : 3);

	// check not on edge: if on edge -1 posibility
	if (!(x-1) <= (roomWidthFloor-1-1)) maxRoomsToCreate -= 1;
	if (!(y-1) <= (roomHeightFloor-1-1)) maxRoomsToCreate -= 1;


	if(){
	}
}