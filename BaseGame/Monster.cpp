#include "Monster.h"

Monster::Monster(std::string_view name, std::string_view img, const Status& stat, int r_gold, int r_exp) :
	BattleEntity(name, img, stat), reward_gold(r_gold), reward_exp(r_exp)
{
}

void Monster::Render()
{
	// ·»´õ¸µ
}

int Monster::GetRewardExp() const
{
	return reward_exp;
}

int Monster::GetRewardGold() const
{
	return reward_gold;
}

