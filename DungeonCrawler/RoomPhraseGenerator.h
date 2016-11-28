#pragma once

class RoomPhraseGenerator
{
	typedef vector<string> RoomAttributeList;
	typedef vector<RoomAttributeList*> RoomDefenitionList;

	public:
		~RoomPhraseGenerator();
		static RoomPhraseGenerator &getInstance();

		string * CreateRoomPhrase();
		string CreateHallPhrase();

	private:
		RoomPhraseGenerator();
		RoomPhraseGenerator(RoomPhraseGenerator const&);
		void operator=(RoomPhraseGenerator const&);

		RoomDefenitionList * roomDefenitions;
		vector<string> * hallDefenitions;
};
