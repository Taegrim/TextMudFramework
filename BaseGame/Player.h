#pragma once
#include "BattleEntity.h"

class Player : public BattleEntity
{
public:
	Player(std::string_view name, std::string_view img, const Status& stat);

	void Render() override;

	void GainExp(int amount);
	void GainGold(int amount);
	void Heal(int amount);
	void MaxHeal();

	int GetLevel() const;
	int GetExp() const;
	int GetGold() const;

private:
	int level = 1;
	int exp = 0;
	int gold = 0;

	int GetRequiredExp() const;
};

