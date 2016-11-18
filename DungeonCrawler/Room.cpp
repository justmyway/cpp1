#include "stdafx.h"
#include "Room.h"


Room::Room()
{
	neightbors = vector<tuple<Neighbor, Room*>>();
}


Room::~Room()
{
}

void Room::ConnectNeighbor(Neighbor side, Room * room)
{
	for (auto const& neightbor : neightbors) {
		if (get<0>(neightbor) == side) return;
	}

	neightbors.push_back(make_tuple(side, room));
	//need to link other way around
}
