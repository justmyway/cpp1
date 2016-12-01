#pragma once

#include "Enemy.h";

class EnemyGenerator
{
	public:
		static EnemyGenerator &getInstance();
		Enemy * GenerateEnemy(int);

	private:
		EnemyGenerator();
		EnemyGenerator(EnemyGenerator const&);
		void operator=(EnemyGenerator const&);

		vector<Enemy>
};

