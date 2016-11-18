#pragma once
class Room
{
public:
	Room();
	~Room();

	void ConnectNeighbor(Neighbor, Room*);

private:
	vector<tuple<Neighbor, Room*>> neightbors;
};

