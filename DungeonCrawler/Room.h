#pragma once

class Hero;
class Enemy;
class CarryItem;

class FightGamePhase;

class Room
{
	public:
		Room(int);
		~Room();

		string * description;
		
		void Enter(Hero*, bool);
		vector<Neighbor> * MoveOptions();
		void MoveTo(Neighbor);
		bool Visited();
		int AmountOfEnemies();
		int AmountOfItems();

		vector<Enemy*> * GetEnemies();

		void SetEndBoss();
		void GenEnemies();
		string ToString();
		string ToStringSouthCoridor();
		void ConnectNeighbor(Neighbor, Room*);
	
	private:
		bool startfield = false;
		bool visited = false;
		Hero * player;
		int floorLevel;
		bool noEnemies;
		vector<tuple<Neighbor, Room *>> * neighbors;

		bool NeighborExists(Neighbor);
		Room * GetNeighbor(Neighbor);

		vector<Enemy *> * enemies;
		vector<CarryItem *> * items;
};

