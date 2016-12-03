#pragma once

#include "Enemy.h"

class EnemyGenerator
{
	public:
		~EnemyGenerator();
		static EnemyGenerator &getInstance();
		Enemy * GenerateEnemy(int);

	private:
		EnemyGenerator();
		EnemyGenerator(EnemyGenerator const&);
		void operator=(EnemyGenerator const&);

		unsigned int split(std::string &, std::vector<std::string>&, char);

		vector<Enemy*> * enemies;
};

