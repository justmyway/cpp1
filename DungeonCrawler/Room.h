#pragma once

#include "Hero.h":

class Room
{
	public:
		Room();
		~Room();
		
		void Enter(Hero*);
		vector<Neighbor> * MoveOptions();
		void MoveTo(Neighbor);

		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room*);
	
	private:
		bool visited = false;
		Hero * player;
		vector<tuple<Neighbor, Room *>> * neightbors;
		string * description;

		bool NeightborExists(Neighbor);
};

