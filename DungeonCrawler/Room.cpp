#include "stdafx.h"

#include "RoomPhraseGenerator.h"
#include "Enemygenerator.h"
#include "itemGenerator.h"

#include "Room.h"
#include "Hero.h"

Room::Room(int newfloorLevel)
{
	neighbors = new vector<tuple<Neighbor, Room *>>();
	description = RoomPhraseGenerator::getInstance().CreateRoomPhrase();
	enemies = new vector<Enemy *>();
	items = ItemGenerator::getInstance().GenerateRoomItems();

	floorLevel = newfloorLevel;
	noEnemies = true;
}


Room::~Room()
{
	delete description;
	delete neighbors;
	for (auto const& item : *items) {
		delete item;
	}
	items->clear();
	for (auto const& enemy : *enemies) {
		delete enemy;
	}
	enemies->clear();
	delete items;
	delete enemies;
}

void Room::Enter(Hero * playerEnter, bool start = false) {
	startfield = start;
	visited = true;
	player = playerEnter;

	if (enemies->size() == 0 && !noEnemies) {
		//srand(time_t(0));
		int amountOfEnemies = rand() % 3;
		for (int i = 0; i < amountOfEnemies; i++) {
			enemies->push_back(EnemyGenerator::getInstance().GenerateEnemy(floorLevel));
		}
	}
}

vector<Neighbor> Room::MoveOptions() {
	vector<Neighbor> returnNeighbors = vector<Neighbor>();

	for (auto const& neighbor : *neighbors)
		returnNeighbors.push_back(get<0>(neighbor));

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

int Room::AmountOfItems()
{
	return items->size();
}

vector<Enemy*>* Room::GetEnemies()
{
	return enemies;
}

vector<CarryItem*>* Room::GetItems()
{
	vector<CarryItem*> * allItems = new vector<CarryItem*>();

	for (auto item : *items) {
		allItems->push_back(item);
	}
	items->clear();

	return allItems;
}

void Room::SetEndBoss()
{
	enemies->push_back(EnemyGenerator::getInstance().GenerateEnemy(99));
}

void Room::GenEnemies()
{
	int amountOfEnemies = rand() % 2 + 1;
	for (int i = 0; i < amountOfEnemies; i++) {
		enemies->push_back(EnemyGenerator::getInstance().GenerateEnemy(floorLevel));
	}
}

bool Room::StartRoomOfFloor()
{
	return NeighborExists(Neighbor::Up);
}

string Room::ToString() {
	string rep;

	if (!visited) {
		rep += ".";
	}
	else {
		if (player != NULL) {
			rep += "P";
		} else if (startfield) {
			rep += "S";
		} else if (enemies->size() == 1 && enemies->at(0)->GetLevel() == 99) {
			rep += "E";
		} else if (NeighborExists(Neighbor::Down)) {
			rep += "L";
		} else if (NeighborExists(Neighbor::Up)) {
			rep += "H";
		} else {
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