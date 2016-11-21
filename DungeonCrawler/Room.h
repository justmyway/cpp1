#pragma once
class Room
{
public:
	Room();
	~Room();

	void Use();
	bool IsInitialized();
	void ConnectNeighbor(Neighbor, Room*);
	
private:
	bool initiallized;
	vector<tuple<Neighbor, Room*>> neightbors;
	string * description;
};

