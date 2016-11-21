#include "stdafx.h"
#include "Game.h"

#include "RoomGenerator.h"

Game::Game()
{
}


Game::~Game()
{
}


void Game::Play() {
	ConsoleWriter::getInstance().WriteLine("A new game will be started");
	RoomGenerator::getInstance().GenerateFloor(0, 0);
}