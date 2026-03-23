#pragma once
#include "common.h"
#include "BattleEntity.h"

class Item;

class Monster : public BattleEntity
{
public:
	Monster();
	Monster(std::string_view name, std::string_view img, const Status& stat, int gold, int exp);

	void Render() override;

	// 재사용을 위한 초기화 함수
	void Spawn(std::string_view name, std::string_view img, const Status& stat, int gold, int exp);

	// 드롭 테이블 함수
	void SetDropTable(const DropTable* table);
	std::vector<std::unique_ptr<Item>> CheckDrops() const;

	int GetRewardExp() const;
	int GetRewardGold() const;
	
private:
	int reward_gold;
	int reward_exp;
	const DropTable* drop_table = nullptr;
};

