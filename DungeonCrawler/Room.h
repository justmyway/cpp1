#pragma once
class Room
{
	public:
		Room();
		~Room();

		void Use();
		bool IsInitialized();
		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room);
	
	private:
		bool initiallized = false;
		bool visited = false;
		vector<tuple<Neighbor, Room>> * neightbors;
		string * description;

		bool NeightborExists(Neighbor);
};

