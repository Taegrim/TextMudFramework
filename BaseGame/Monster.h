#pragma once
#include "BattleEntity.h"

class Monster : public BattleEntity
{
public:
	Monster();
	Monster(std::string_view name, std::string_view img, const Status& stat, int gold, int exp);

	void Render() override;
	
	int GetRewardExp() const;
	int GetRewardGold() const;
	
	// 재사용을 위한 초기화 함수
	void Spawn(std::string_view name, std::string_view img, const Status& stat, int gold, int exp);

private:
	int reward_gold;
	int reward_exp;
};

