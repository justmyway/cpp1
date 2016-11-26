#include "stdafx.h"

#include "RoomPhraseGenerator.h"
#include "Room.h"
#include "Hero.h"

Room::Room()
{
	neightbors = new vector<tuple<Neighbor, Room *>>();
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
}


Room::~Room()
{
	delete description;
	delete neightbors;
}

void Room::Enter(Hero * playerEnter) {
	player = playerEnter;
	//player->MoveTo(this);
}

vector<Neighbor> * Room::MoveOptions() {
	vector<Neighbor> * neighbors = new vector<Neighbor>();

	for (auto const& neightbor : *neightbors)
		neighbors->push_back(get<0>(neightbor));

	return neighbors;
}

void Room::MoveTo(Neighbor side) {
	for (auto const& neightbor : *neightbors) {
		if (get<0>(neightbor) == side) {
			get<1>(neightbor)->Enter(player);
			player->MoveTo(get<1>(neightbor));
			player = NULL;
		}
	}
}

string Room::ToString() {
	string toString = "N";
	
	if(player != NULL)
		toString = "P";

	/*if (visited) {
		toString += "N";
	} else {
		toString += ". ";
	}*/

	if (NeightborExists(Neighbor::East)) {
		toString += "--";
	} else {
		toString += "  ";
	}

	return toString;
}

string Room::ToStringSouthCoridor() {
	if (NeightborExists(Neighbor::South)) {
		return "|  ";
	}
	return "   ";
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
