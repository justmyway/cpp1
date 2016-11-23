#include "stdafx.h"
#include "Room.h"
#include "RoomPhraseGenerator.h"


Room::Room()
{
	neightbors = new vector<tuple<Neighbor, Room *>>();
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
}


Room::~Room()
{
	delete neightbors;
}

string Room::ToString() {
	string toString = "";

	if (visited) {
		toString += "N";
	} else {
		toString += ".";
	}

	if (NeightborExists(Neighbor::East)) {
		toString += "-";
	} else {
		toString += " ";
	}

	return toString;
}

string Room::ToStringSouthCoridor() {
	string toString = "";

	if (NeightborExists(Neighbor::South)) {
		toString += "|";
	} else {
		toString += " ";
	}

	return toString += " ";
}

void Room::ConnectNeighbor(Neighbor side, Room * room)
{
	for (auto const& neightbor : *neightbors) {
		if (get<0>(neightbor) == side) return;
	}

	neightbors->push_back(make_tuple(side, room));
}

bool Room::NeightborExists(Neighbor side)
{
	for (auto const& neightbor : *neightbors)
		if (get<0>(neightbor) == side) 
			return true;

	return false;
}
