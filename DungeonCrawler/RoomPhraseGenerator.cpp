#include "stdafx.h"
#include "Generator.h"

#include "RoomPhraseGenerator.h"


RoomPhraseGenerator::RoomPhraseGenerator()
{
	RoomAttributeList optionOne{ "Je staat in een kamer", "Je loop in een droom" };

	RoomAttributeList optionTwo{ "met in het midden een tafel.", "waar het heel donker is.", "waar het heel erg stinkt." };

	RoomAttributeList optionThree{ "met in het midden een tafel. Om de tafel staan vier stoelen", "waar het heel donker is.", "waar het heel erg stinkt." };

	RoomAttributeList optionFour{ "In de hoek staat een kist.", "Over het plafont klimt een rat!", "Er klinkt een geluid in de verte..."};


	_roomDefenitions = {optionOne, optionTwo, optionThree, optionFour};
}

RoomPhraseGenerator & RoomPhraseGenerator::getInstance() {
	static RoomPhraseGenerator instance;
	return instance;
}

string * RoomPhraseGenerator::CreateRoomPhrase()
{
	default_random_engine generator;
	generator.seed(time(0));

	string phrase = "";

	bool firstPart = true;

	for (RoomDefenitionList::iterator outer = _roomDefenitions.begin(); outer != _roomDefenitions.end(); ++outer) {
		uniform_int_distribution<int> distribution(0, outer->size());
		if (firstPart) {
			firstPart = false;
		}else{
			phrase += " ";
		}
		phrase += outer->at(distribution(generator));
	}

	return &phrase;
}
