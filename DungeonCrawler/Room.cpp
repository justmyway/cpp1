#include "stdafx.h"

#include "RoomPhraseGenerator.h"

#include "Room.h"
#include "Hero.h"

Room::Room()
{
	neighbors = new vector<tuple<Neighbor, Room *>>();
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
}


Room::~Room()
{
	delete description;
	delete neighbors;
}

void Room::Enter(Hero * playerEnter) {
	visited = true;
	player = playerEnter;
}

vector<Neighbor> * Room::MoveOptions() {
	vector<Neighbor> * returnNeighbors = new vector<Neighbor>();

	for (auto const& neighbor : *neighbors)
		returnNeighbors->push_back(get<0>(neighbor));

	return returnNeighbors;
}

void Room::MoveTo(Neighbor side) {
	for (auto const& neightbor : *neighbors) {
		if (get<0>(neightbor) == side) {
			get<1>(neightbor)->Enter(player);
			player->MoveTo(get<1>(neightbor));
			player = NULL;
		}
	}
}

bool Room::Visited()
{
	return visited;
}

int Room::AmountOfEnemies()
{
	return 0;
}

string Room::ToString() {
	string rep;

	if (!visited) {
		rep += ".";
	}
	else {
		if (player != NULL) {
			rep += "P";
		}
		else {
			rep += "N";
		}
	}

	if (NeighborExists(Neighbor::East)) {
		if (visited || GetNeighbor(Neighbor::East)->Visited())
			return rep += "--";
	}

	return rep += "  ";
}

string Room::ToStringSouthCoridor() {

	if (NeighborExists(Neighbor::South)) {
		if (visited || GetNeighbor(Neighbor::South)->Visited())
			return "|  ";
	}

	return "   ";
}

void Room::ConnectNeighbor(Neighbor side, Room * room)
{
	for (auto const& neightbor : *neighbors) {
		if (get<0>(neightbor) == side) return;
	}

	neighbors->push_back(make_tuple(side, room));
}

bool Room::NeighborExists(Neighbor side)
{
	return GetNeighbor(side) != NULL;
}

Room * Room::GetNeighbor(Neighbor side)
{
	for (auto const& neighbor : *neighbors)
		if (get<0>(neighbor) == side)
			return get<1>(neighbor);

	return NULL;
}