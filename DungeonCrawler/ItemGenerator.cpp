#include "stdafx.h"
#include "ItemGenerator.h"

#include "Armour.h"
#include "Posion.h"


ItemGenerator::ItemGenerator()
{
	allItems = new vector<CarryItem*>();

	allItems->push_back(new Armour("Romijnse helm", "geeft meer verdedigings kans(5%)", 0, 0, 0, 5));
}


ItemGenerator::~ItemGenerator()
{
	for (auto const& item : *allItems) {
		delete item;
	}

	allItems->clear();

	delete allItems;
}

ItemGenerator & ItemGenerator::getInstance()
{
	static ItemGenerator instance;
	return instance;
}

vector<CarryItem*>* ItemGenerator::GenerateRoomItems()
{
	int amount = rand() % 3;

	vector<CarryItem*> * items = new vector<CarryItem*>();

	while (amount != 0) {
		int index = rand() % allItems->size();
		
		items->push_back(allItems->at(index)->Clone());

		amount--;
	}

	return items;
}
