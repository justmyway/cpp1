#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

#include <algorithm>

#include "EnemyGenerator.h"

#include "FileReader.h"

using std::min;


EnemyGenerator::EnemyGenerator()
{
	srand((unsigned)time(NULL));

	enemies = new vector<Enemy*>();

	vector<string> * monsters = FileReader::getInstance().ReadFile("C:\\Dungeon Crawler\\monsters.txt", true);
	for (auto const& monster : *monsters) {
		//stripping [ and ]
		string monsterLine = monster.substr(1, monster.size() - 2);

		//devide by ;
		vector<string> * monsterCharacteristics = new vector<string>();
		split(monsterLine, *monsterCharacteristics, ';');

		//get attack
		vector<string> * monsterAttackCharacteristics = new vector<string>();
		unsigned int pos = monsterCharacteristics->at(2).find("x");
		monsterAttackCharacteristics->push_back(monsterCharacteristics->at(2).substr(0, pos));
		monsterAttackCharacteristics->push_back(monsterCharacteristics->at(2).substr(pos+1, (monsterCharacteristics->at(2).size())));

		//min - max attack
		vector<string> * monsterAttackPointsCharacteristics = new vector<string>();
		pos = monsterCharacteristics->at(3).find("-");
		monsterAttackPointsCharacteristics->push_back(monsterCharacteristics->at(3).substr(0, pos));
		monsterAttackPointsCharacteristics->push_back(monsterCharacteristics->at(3).substr(pos + 1, (monsterCharacteristics->at(3).size())));

		monsterCharacteristics->at(0);
		monsterCharacteristics->at(1);

		enemies->push_back(new Enemy(
			monsterCharacteristics->at(0),
			monsterCharacteristics->at(1),
			ToInt(monsterAttackCharacteristics->at(1)),
			ToInt(monsterAttackCharacteristics->at(0)),
			ToInt(monsterAttackPointsCharacteristics->at(0)),
			ToInt(monsterAttackPointsCharacteristics->at(1)),
			ToInt(monsterCharacteristics->at(4)),
			ToInt(monsterCharacteristics->at(5))
		));

		delete monsterCharacteristics;
		delete monsterAttackCharacteristics;
		delete monsterAttackPointsCharacteristics;
	}
}

EnemyGenerator::~EnemyGenerator()
{
	for (vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end(); ++it)
	{
		delete (*it);
	}
	enemies->clear();
	delete enemies;
}

EnemyGenerator & EnemyGenerator::getInstance()
{
	static EnemyGenerator instance;
	return instance;
}

Enemy * EnemyGenerator::GenerateEnemy(int level)
{
	int minLevel = 1;
	if (level - 1 >= 1)
		minLevel = level - 1;

	int maxLevel = 10;
	if (level + 1 <= 10)
		maxLevel = level + 1;

	Enemy * returnEnemy = NULL;

	while (returnEnemy == NULL) {
		int index = rand() % enemies->size();

		if (level == 99 && enemies->at(index)->GetLevel() == 99) {
			return enemies->at(index)->Clone();
		}

		if (enemies->at(index)->GetLevel() >= minLevel && enemies->at(index)->GetLevel() <= maxLevel)
			returnEnemy = enemies->at(index)->Clone();
	}

	return returnEnemy;
}

unsigned int EnemyGenerator::split(std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		//strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	int smallest = pos;
	if (smallest > txt.size())
		smallest = txt.size();

	// Add the last one
	//strs.push_back(txt.substr(initialPos, (std::min(pos, txt.size()) - initialPos + 1)));
	strs.push_back(txt.substr(initialPos, (smallest) - initialPos + 1));

	return strs.size();
}
