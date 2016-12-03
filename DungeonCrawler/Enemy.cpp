#include "stdafx.h"
#include "Enemy.h"

#include <time.h>
#include <stdlib.h>

Enemy::Enemy()
{
}

Enemy::Enemy(string nName, string nLevel, int nAttackAmount, int nHitChance, int nMinDamage, int nMaxDamage, int nDefeneChance, int nLifePoints)
	: name(nName), level(nLevel), attackAmount(nAttackAmount), hitChance(nHitChance), minDamage(nMinDamage), maxDamage(nMaxDamage), defenceChance(nDefeneChance), lifePoints(nLifePoints), xp(nLifePoints)
{
}

Enemy::~Enemy()
{
}

Enemy * Enemy::Clone()
{
	return nullptr;
}

string Enemy::ToString()
{
	return "Een " + name + " met " + to_string(lifePoints) + " levens.";
}

int Enemy::GetLevel()
{
	if(level != "BAAS")
		return ToInt(level);

	return 99;
}

string Enemy::GetName()
{
	return name;
}

int Enemy::DiedGetxp()
{
	if (lifePoints <= 0)
		return xp;

	return 0;
}

bool Enemy::TakeDamage(int strength)
{
	srand(time_t(0));
	int change = rand() % 100 + 1;

	if (defenceChance < change) {
		lifePoints -= strength;
		return true;
	}

	return false;
}
