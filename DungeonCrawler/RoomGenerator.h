#pragma once
#include "Room.h";


class RoomGenerator
{
	public:
		static RoomGenerator &getInstance();

		void setFloorDimensions(const int, const int);
		Room * GenerateFloor();

	private:
		RoomGenerator();
		RoomGenerator(RoomGenerator const&);
		void operator=(RoomGenerator const&);

		int _roomWidthFloor;
		int _roomHeightFloor;
};

