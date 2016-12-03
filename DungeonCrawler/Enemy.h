#pragma once
class Enemy
{
	public:
		Enemy();
		Enemy(string, string, int, int, int, int, int, int);
		~Enemy();

		Enemy * Clone();
		string ToString();

		int GetLevel();
		string GetName();
		int GetPower();
		int DiedGetxp();
		bool TakeDamage(int);

	private:
		string name;
		string level;
		int attackAmount;
		int xp;
		int hitChance;
		int minDamage;
		int maxDamage;
		int defenceChance;
		int lifePoints;
};

