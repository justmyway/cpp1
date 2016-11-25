#pragma once
class Room
{
	public:
		Room();
		~Room();

		bool IsInitialized();
		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room*);
	
	private:
		bool visited = false;
		vector<tuple<Neighbor, Room *>> * neightbors;
		string * description;

		bool NeightborExists(Neighbor);
};

