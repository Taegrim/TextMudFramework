#pragma once
#include "common.h"

class Player;
class Monster;

class BattleManager 
{
public:
	BattleManager(Player* p);
	~BattleManager() = default;

	void StartBattle(Monster* m);
	void PlayerAttack();
	void MonsterAttack();

	bool IsBattleOver() const;
	Monster* GetMonster() const;

private:
	Player* player = nullptr;
	Monster* monster = nullptr;
};

