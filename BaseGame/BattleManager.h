#pragma once
#include "common.h"

class Player;
class Monster;
class Item;

class BattleManager 
{
public:
	BattleManager(Player* p);
	~BattleManager() = default;

	void StartBattle(const std::vector<Monster*>& monsters);
	void PlayerAttack(int target_idx);
	void MonsterAttack();

	bool IsBattleOver() const;
	bool IsPlayerVictory() const;
	void DistributeReward();	// 전투 종료시 보상 지급

	int GetTotalExp() const;

private:
	Player* player = nullptr;
	std::vector<Monster*> monster_list;
	int total_exp = 0;
	int total_gold = 0;
	std::vector<std::unique_ptr<Item>> items;
};

