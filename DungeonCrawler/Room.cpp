#include "stdafx.h"

#include "RoomPhraseGenerator.h"
#include "Enemygenerator.h"

#include "Room.h"
#include "Hero.h"

Room::Room()
{
	neighbors = new vector<tuple<Neighbor, Room *>>();
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
	enemies = new vector<Enemy * >();

	floorLevel = 1;
}


Room::~Room()
{
	delete description;
	delete neighbors;
}

void Room::Enter(Hero * playerEnter) {
	visited = true;
	player = playerEnter;

	if (enemies->size() == 0) {
		srand(time_t(0));
		int amountOfEnemies = rand() % 3;
		for (int i = 0; i < amountOfEnemies; i++) {
			enemies->push_back(EnemyGenerator::getInstance().GenerateEnemy(floorLevel));
		}
	}
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
	return enemies->size();
}

vector<Enemy*>* Room::GetEnemies()
{
	return enemies;
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