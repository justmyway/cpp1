// DungeonCrawler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
	ConsoleWriter::getInstance().WriteLine("*---* DUNGEON GAME STARTED *---*");
	
	Game *game = new Game();

	game->Play();

	delete game;

	ConsoleWriter::getInstance().WriteLine("*---* DUNGEON GAME ENDED *---*");
	ConsoleWriter::getInstance().WriteLine("*---* Game will be stoped *---*");
	system("PAUSE");
    return 0;
}

