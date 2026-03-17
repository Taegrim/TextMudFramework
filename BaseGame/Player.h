#pragma once
#include "BattleEntity.h"

class Player : public BattleEntity
{
public:
	Player(std::string_view name, std::string_view img, const Status& stat);

	void Render() override;

	void GainExp(int amount);

private:
	int level = 1;
	int exp = 0;
	int gold = 0;
};

