#pragma once
#include <vector>
#include <memory>

class Player;
class Monster;
class Item;

class BattleManager 
{
public:
	BattleManager(Player* p);
	~BattleManager() = default;

	void StartBattle(const std::vector<Monster*>& monsters);
	void PlayerAttack(size_t target_idx);
	void MonsterAttack();

	bool IsBattleOver() const;
	bool IsPlayerVictory() const;
	void DistributeReward();	// 전투 종료시 보상 지급

	unsigned int GetTotalExp() const;

private:
	Player* player = nullptr;
	std::vector<Monster*> monster_list;
	unsigned int total_exp = 0;
	unsigned int total_gold = 0;
	std::vector<std::unique_ptr<Item>> items;
};

