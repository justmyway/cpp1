#include "stdafx.h"
#include "Room.h"
#include "RoomPhraseGenerator.h"


Room::Room()
{
	neightbors = vector<tuple<Neighbor, Room*>>();
	initiallized = false;
}


Room::~Room()
{
}

void Room::Use() {
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
	initiallized = true;
}

bool Room::IsInitialized()
{
	return initiallized;
}

void Room::ConnectNeighbor(Neighbor side, Room * room)
{
	for (auto const& neightbor : neightbors) {
		if (get<0>(neightbor) == side) return;
	}

	neightbors.push_back(make_tuple(side, room));
	//need to link other way around
}
