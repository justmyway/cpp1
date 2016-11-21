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
	floor = new Room*[beginX];
	for (size_t i = 0; i < beginX; i++) {
		floor[i] = new Room[beginY];
	}
	
	floor[beginX][beginY].Use();

	//create floor
	CreateNeighbors(floor[beginX][beginY], beginX, beginY, 1);
	
	return &floor[beginX][beginY];
}

void RoomGenerator::CreateNeighbors(Room room, int x, int y, int amountOfRooms) {
	// determ max rooms to create: first has 4 posibilities
	unsigned int maxRoomsToCreate = (amountOfRooms == 1 ? 4 : 3);

	// check not on edge: if on edge -1 possibility
	if (!(x-1) <= (roomWidthFloor-1-1)) maxRoomsToCreate--;
	if (!(y-1) <= (roomHeightFloor-1-1)) maxRoomsToCreate--;

	//amount of rooms
	int roomsToCreate = rand() % (maxRoomsToCreate + 1);

	vector<tuple<int, int, Neighbor>> posibleNeighbors = RandomPosibleNeighbors(x, y);

	while (roomsToCreate != 0)
	{
		//niet meer dan 50% van de map mag kamer zijn
		if (amountOfRooms >= (x*y)/2) return;

		//checking if neighbors to make
		if (posibleNeighbors.size() == 0) return;

		//take first of posible neighbors to try
		tuple<int, int, Neighbor> posibleNeighbor = move(posibleNeighbors.back());
		posibleNeighbors.pop_back();

		if (floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)]) {
			//create new room and link

		}
		else {
			//link to current
			room.ConnectNeighbor(get<2>(posibleNeighbor), floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)]);
		}

		roomsToCreate--;
	}
}

vector<tuple<int, int, Neighbor>> RoomGenerator::RandomPosibleNeighbors(int x, int y)
{
	vector<tuple<int, int, Neighbor>> neighbors = vector<tuple<int, int, Neighbor>>();

	if (y + 1 < roomHeightFloor) neighbors.push_back(make_tuple(x, y+1, Neighbor::North));
	if (x + 1 < roomWidthFloor) neighbors.push_back(make_tuple(x+1, y, Neighbor::East));
	if (y - 1 >= 0) neighbors.push_back(make_tuple(x, y-1, Neighbor::South));
	if (x - 1 >= 0) neighbors.push_back(make_tuple(x-1, y, Neighbor::West));

	random_shuffle(neighbors.begin(), neighbors.end());
	
	return neighbors;
}
