#pragma once
#include "Room.h";
#include "StairRoom.h";

class RoomGenerator
{
	public:
		static RoomGenerator &getInstance();

		void setFloorDimensions(const int, const int);
		Room * GenerateFloor(int, int);

	private:
		RoomGenerator();
		RoomGenerator(RoomGenerator const&);
		void operator=(RoomGenerator const&);

		int roomWidthFloor;
		int roomHeightFloor;

		Room** floor;

		void CreateNeighbors(Room, int, int, int);
		vector<tuple<int, int, Neighbor>> RandomPosibleNeighbors(int, int);
};

