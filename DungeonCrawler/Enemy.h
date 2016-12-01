#pragma once
class Enemy
{
	public:
		Enemy(string, int, int, int, int, int, int);
		~Enemy();

		Enemy * clone();

	private:
		string name;
		int level;
		int attackAmount;
		int hitChance;
		int damage;
		int defenceChance;
		int lifePoints;
};

