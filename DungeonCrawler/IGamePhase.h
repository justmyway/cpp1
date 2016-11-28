#pragma once

class Hero;
class Room;
class Game;

class IGamePhase
{
	public:
		IGamePhase(Hero *, Game *);
		~IGamePhase();

		virtual void Run() = 0;

	protected:
		virtual vector<string> CreateActions() = 0;

		Hero * player;
		Game * game;
};

