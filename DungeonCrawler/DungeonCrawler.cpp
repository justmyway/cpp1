// DungeonCrawler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif 

	ConsoleWriter::getInstance().WriteLine("*---* DUNGEON GAME STARTED *---*");
	
	Game *game = new Game();

	game->Play();

	delete game;

	ConsoleWriter::getInstance().WriteLine("*---* DUNGEON GAME ENDED *---*");
	ConsoleWriter::getInstance().WriteLine("*---* Game will be stoped *---*");
	system("PAUSE");
    return 0;
}

