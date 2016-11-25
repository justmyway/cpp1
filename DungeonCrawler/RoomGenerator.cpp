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

Room *** RoomGenerator::GenerateFloor(int beginX, int beginY) {
	floor = new Room**[roomWidthFloor];
	for (int x = 0; x < roomWidthFloor; x++) {
		floor[x] = new Room*[roomHeightFloor];
		for (int y = 0; y < roomHeightFloor; y++) {
			floor[x][y] = NULL;
		}
	}

	floor[beginX][beginY] = new Room();

	//create floor
	CreateNeighbors(floor[beginX][beginY], beginX, beginY, 1);
	
	return floor;
}

int RoomGenerator::CreateNeighbors(Room * room, int x, int y, int amountOfRooms) {
	// determ max rooms to create: first has 4 posibilities
	unsigned int maxRoomsToCreate = (amountOfRooms == 1 ? 4 : 3);

	// check not on edge: if on edge -1 possibility
 	if (!InbetweenMap(x, roomWidthFloor)) maxRoomsToCreate--;
	if (!InbetweenMap(y, roomHeightFloor)) maxRoomsToCreate--;

	//amount of rooms
	int roomsToCreate = maxRoomsToCreate;
	if (maxRoomsToCreate != 4)
		roomsToCreate = rand() % (maxRoomsToCreate + 1);

	int amountOfTotalRooms = amountOfRooms + roomsToCreate;

	vector<tuple<int, int, Neighbor>> posibleNeighbors = RandomPosibleNeighbors(x, y);

	while (roomsToCreate != 0)
	{
		//niet meer dan 50% van de map mag kamer zijn
		if (amountOfTotalRooms >= (roomHeightFloor*roomWidthFloor)/2) return amountOfTotalRooms;

		//checking if neighbors to make
		if (posibleNeighbors.size() == 0) return amountOfTotalRooms;

		//take first of posible neighbors to try
		tuple<int, int, Neighbor> posibleNeighbor = posibleNeighbors.back();
		posibleNeighbors.pop_back();

		if (floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)] == NULL) {
			//cout << "x: " + std::to_string(get<0>(posibleNeighbor)) + "    y: " + std::to_string(get<1>(posibleNeighbor)) << endl;
			floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)] = new Room();
		}

		//linking rooms
		room->ConnectNeighbor(get<2>(posibleNeighbor), floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)]);
		floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)]->ConnectNeighbor(GetOppositeSide(get<2>(posibleNeighbor)), room);

		floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)] = floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)];

		//creating new rooms
		int returnRoomAmount = CreateNeighbors(floor[get<0>(posibleNeighbor)][get<1>(posibleNeighbor)], get<0>(posibleNeighbor), get<1>(posibleNeighbor), amountOfTotalRooms);
		if (returnRoomAmount > amountOfTotalRooms)
			amountOfTotalRooms = returnRoomAmount;

		roomsToCreate--;
	}

	return amountOfTotalRooms;
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

Neighbor RoomGenerator::GetOppositeSide(Neighbor side) {
	return (side <= 1 ? static_cast<Neighbor>(side+2) : static_cast<Neighbor>(side - 2));
}

bool RoomGenerator::InbetweenMap(int a, int b)
{
	return a >= 1 && a < b-1;
}