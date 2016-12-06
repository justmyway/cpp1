#include "stdafx.h"
#include "ItemGenerator.h"

#include "Armour.h"
#include "Posion.h"


ItemGenerator::ItemGenerator()
{
	allItems = new vector<CarryItem*>();

	allItems->push_back(new Armour("Romijnse helm", "geeft meer verdedigings kans(+5%)", 0, 0, 0, 5));
	allItems->push_back(new Armour("Hardloop schoenen", "geeft meer aanvals kans(+5%)", 0, 0, 5, 0));
	allItems->push_back(new Armour("Hart van Theos", "geeft meer levens punten (+5)", 5, 0, 0, 0));
	allItems->push_back(new Armour("De hamer van Thorr", "geeft aanvals kracht (+5)", 0, 5, 0, 0));
	allItems->push_back(new Armour("Stekel van knorretje", "geeft aanvals kracht (+2)", 0, 2, 0, 0));

	allItems->push_back(new Posion("Slangen van Medusa", "geeft aanvals kans (100%)", 0, 0, 100, 0));
	allItems->push_back(new Posion("Defensis mensis", "geeft verdedings kans (+30%)", 0, 0, 0, 30));
	allItems->push_back(new Posion("Health", "Geeft levens(+30)", 30, 0, 0, 0));
	allItems->push_back(new Posion("Health", "Geeft levens(+20)", 20, 0, 0, 0));
	allItems->push_back(new Posion("Health", "Geeft levens(+10)", 10, 0, 0, 0));
	allItems->push_back(new Posion("Poppai power", "Geeft kracht(+20)", 0, 20, 0, 0));

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
