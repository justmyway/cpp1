#include "stdafx.h"
#include "EnemyGenerator.h"

#include "FileReader.h"


EnemyGenerator::EnemyGenerator()
{
	vector<string> * monsters = FileReader::getInstance().ReadFile("C:\monsters.txt", true);
	for (auto const& monster : *monsters) {
	
	}
}

EnemyGenerator & EnemyGenerator::getInstance()
{
	static EnemyGenerator instance;
	return instance;
}

Enemy * EnemyGenerator::GenerateEnemy(int)
{
	return new Enemy();
}

