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
	_roomWidthFloor = width;
	_roomHeightFloor = height;
}

Room * RoomGenerator::GenerateFloor() {
	for (int i = 0; i < 10000; i++) {
		ConsoleWriter::getInstance().WriteLine(*RoomPhraseGenerator::getInstance().CreateRoomPhrase());
	}
	return new Room();
}