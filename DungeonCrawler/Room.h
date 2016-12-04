#pragma once

class Hero;
class Enemy;

class FightGamePhase;

class Room
{
	public:
		Room();
		~Room();

		string * description;
		
		void Enter(Hero*);
		vector<Neighbor> * MoveOptions();
		void MoveTo(Neighbor);
		bool Visited();
		int AmountOfEnemies();

		vector<Enemy*> * GetEnemies();

		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room*);
	
	private:
		bool visited = false;
		Hero * player;
		int floorLevel;
		bool noEnemies;
		vector<tuple<Neighbor, Room *>> * neighbors;

		bool NeighborExists(Neighbor);
		Room * GetNeighbor(Neighbor);

		vector<Enemy *> * enemies;
};

