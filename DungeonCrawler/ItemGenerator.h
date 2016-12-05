#pragma once

#include "CarryItem.h"

class ItemGenerator
{
public:
	~ItemGenerator();
	static ItemGenerator &getInstance();

	vector<CarryItem*> * GenerateRoomItems();
	
private:
	ItemGenerator();
	ItemGenerator(ItemGenerator const&);
	void operator=(ItemGenerator const&);

	vector<CarryItem*> * allItems;
};

