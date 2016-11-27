#pragma once

class Hero;

class Room
{
	public:
		Room();
		~Room();
		
		void Enter(Hero*);
		vector<Neighbor> * MoveOptions();
		void MoveTo(Neighbor);
		bool Visited();

		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room*);
	
	private:
		bool visited = false;
		Hero * player;
		vector<tuple<Neighbor, Room *>> * neighbors;
		string * description;

		bool NeighborExists(Neighbor);
		Room * GetNeighbor(Neighbor);
};

