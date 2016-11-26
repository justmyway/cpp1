#pragma once
#include "Room.h"
#include "StairRoom.h"

class RoomGenerator
{
	public:
		static RoomGenerator &getInstance();

		void setFloorDimensions(const int, const int);
		Room *** GenerateFloor(int, int);

	private:
		RoomGenerator();
		RoomGenerator(RoomGenerator const&);
		void operator=(RoomGenerator const&);

		int roomWidthFloor;
		int roomHeightFloor;
		double roomDensity;

		Room*** floor;

		int CreateNeighbors(Room *, int, int, int);
		vector<tuple<int, int, Neighbor>> RandomPosibleNeighbors(int, int);
		Neighbor GetOppositeSide(Neighbor);
		bool InbetweenMap(int, int);
};

