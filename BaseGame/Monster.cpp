#include "Monster.h"

Monster::Monster() : BattleEntity("None", " ", Status()), reward_gold(0), reward_exp(0)
{
	is_visible = false;
}

Monster::Monster(std::string_view name, std::string_view img, const Status& stat, int gold, int exp) :
	BattleEntity(name, img, stat), reward_gold(gold), reward_exp(exp)
{
}

void Monster::Render()
{
	if (!is_visible) {
		return;
	}

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

void Monster::Spawn(std::string_view name, std::string_view img, const Status& stat, int gold, int exp)
{
	this->name = name;
	this->image = img;
	this->status = stat;
	this->reward_gold = gold;
	this->reward_exp = exp;
	this->is_visible = true;
}

