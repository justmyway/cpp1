#pragma once

class RoomPhraseGenerator
{
	typedef vector<string> RoomAttributeList;
	typedef vector<RoomAttributeList> RoomDefenitionList;

	public:
		static RoomPhraseGenerator &getInstance();

		string * CreateRoomPhrase();

	private:
		RoomPhraseGenerator();
		RoomPhraseGenerator(RoomPhraseGenerator const&);
		void operator=(RoomPhraseGenerator const&);

		RoomDefenitionList _roomDefenitions;
};

