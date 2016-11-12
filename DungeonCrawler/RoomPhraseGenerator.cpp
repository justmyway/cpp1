#include "stdafx.h"
#include "Generator.h"

#include "RoomPhraseGenerator.h"


RoomPhraseGenerator::RoomPhraseGenerator()
{
	RoomAttributeList *optionOne = new RoomAttributeList{ "Je staat in een kamer", "Je loop in een droom" };
	RoomAttributeList *optionTwo = new RoomAttributeList{ "met in het midden een tafel.", "waar het heel donker is.", "waar het heel erg stinkt." };
	RoomAttributeList *optionThree = new RoomAttributeList{ "met in het midden een tafel. Om de tafel staan vier stoelen", "waar het heel donker is.", "waar het heel erg stinkt." };
	RoomAttributeList *optionFour = new RoomAttributeList{ "In de hoek staat een kist.", "Over het plafont klimt een rat!", "Er klinkt een geluid in de verte..."};

	roomDefenitions = new RoomDefenitionList{optionOne};

	delete optionOne, optionTwo, optionThree, optionFour;
}

RoomPhraseGenerator::~RoomPhraseGenerator()
{
	delete roomDefenitions;
}

RoomPhraseGenerator & RoomPhraseGenerator::getInstance() {
	static RoomPhraseGenerator instance;
	return instance;
}

string * RoomPhraseGenerator::CreateRoomPhrase()
{
	default_random_engine generator;
	generator.seed(time(0));

	string *phrase = new string();

	bool firstPart = true;

	for (RoomDefenitionList::iterator outer = roomDefenitions->begin(); outer != roomDefenitions->end(); ++outer) {
		uniform_int_distribution<int> distribution(0, (*outer)->size());
		if (firstPart) {
			firstPart = false;
		}else{
			*phrase += " ";
		}
		*phrase += (*outer)->at(distribution(generator));
	}

	return phrase;
}
