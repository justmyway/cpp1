#include "stdafx.h"
#include "Generator.h"

#include "RoomPhraseGenerator.h"


RoomPhraseGenerator::RoomPhraseGenerator()
{
	RoomAttributeList *optionOne = new RoomAttributeList{ "Je staat in een kamer", "Je loop in een droom" };
	RoomAttributeList *optionTwo = new RoomAttributeList{ "met in het midden een tafel.", "waar het heel donker is.", "waar het heel erg stinkt." };
	RoomAttributeList *optionThree = new RoomAttributeList{ "Met in het midden een tafel. Om de tafel staan vier stoelen", "Waar het heel donker is.", "Waar het heel erg stinkt." };
	RoomAttributeList *optionFour = new RoomAttributeList{ "In de hoek staat een kist.", "Over het plafont klimt een rat!", "Er klinkt een geluid in de verte..."};

	roomDefenitions = new RoomDefenitionList{optionOne, optionTwo, optionThree, optionFour};
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

	string *phrase = new string();

	bool firstPart = true;

	for (RoomDefenitionList::iterator outer = roomDefenitions->begin(); outer != roomDefenitions->end(); ++outer) {
		generator.seed((unsigned int)(1000 * (((double)rand()) / RAND_MAX)));
		uniform_int_distribution<int> distribution(0, ((*outer)->size()-1));
		if (firstPart) {
			firstPart = false;
		}else{
			*phrase += " ";
		}
		*phrase += (*outer)->at(distribution(generator));
	}

	return phrase;
}
