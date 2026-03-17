#pragma once
#include "BattleEntity.h"

class Monster : public BattleEntity
{
public:
	Monster(std::string_view name, std::string_view img, const Status& stat, int r_gold, int r_exp);

	void Render() override;
	
	int GetRewardExp() const;
	int GetRewardGold() const;

private:
	int reward_gold;
	int reward_exp;
};

