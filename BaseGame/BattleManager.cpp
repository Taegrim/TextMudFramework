#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"


BattleManager::BattleManager(Player* p) : player(p), monster(nullptr)
{
}

void BattleManager::StartBattle(Monster* m)
{
	monster = m;

	// 전투 초기화
}

void BattleManager::PlayerAttack()
{
	if (!player || !monster || monster->IsDead()) {
		return;
	}

	int atk = player->GetStatus()[StatusType::Atk];
	int damage = monster->TakeDamage(atk);

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[공격] " + std::string(monster->GetName()) + "에게 " + std::to_string(damage) + "데미지를 입혔습니다!");

	if (monster->IsDead()) {
		UIManager::GetInstance().AddMessage(GlobalUIType::Log,
			"[승리] " + std::string(monster->GetName()) + "와(과)의 전투에서 승리하셨습니다!");

		player->GainExp(monster->GetRewardExp());

		monster->SetVisible(false);
	}
}

void BattleManager::MonsterAttack()
{
	if (!player || !monster || monster->IsDead()) {
		return;
	}

	int atk = monster->GetStatus()[StatusType::Atk];
	int damage = player->TakeDamage(atk);

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[피격] " + std::string(monster->GetName()) + "에게 " + std::to_string(damage) + "의 피해를 받았습니다!");

	if (player->IsDead()) {
		UIManager::GetInstance().AddMessage(GlobalUIType::Log,
			"[사망] " + std::string(monster->GetName()) + "에 의해 사망하였습니다...");

		// 사망 처리
	}
}

bool BattleManager::IsBattleOver() const
{
	if (!player || !monster) {
		return true;
	}

	return (player->IsDead() || !monster->IsVisible());
}

Monster* BattleManager::GetMonster() const
{
	return monster;
}
