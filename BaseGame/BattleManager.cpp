#include "BattleManager.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"


BattleManager::BattleManager(Player* p) : player(p)
{
}

void BattleManager::StartBattle(const std::vector<Monster*>& monsters)
{
	monster_list = monsters;

	// 전투 초기화
	total_exp = 0;
	total_gold = 0;
}

void BattleManager::PlayerAttack(int target_idx)
{
	// 플레이어 유효성 확인
	if (!player || player->IsDead()) {
		return;
	}

	// 인덱스 유효성 확인
	if (target_idx < 0 || target_idx >= monster_list.size()) {
		return;
	}
	Monster* monster = monster_list[target_idx];

	// 몬스터 유효성 확인
	if (!monster || monster->IsDead() || !monster->IsVisible()) {
		return;
	}

	int atk = player->GetStatus()[StatusType::Atk];
	int damage = monster->TakeDamage(atk);

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[공격] " + std::string(monster->GetName()) + "[" +  std::to_string(target_idx + 1) +
		"]에게 " + std::to_string(damage) + "데미지를 입혔습니다!");

	if (monster->IsDead()) {
		UIManager::GetInstance().AddMessage(GlobalUIType::Log,
			"[처치] " + std::string(monster->GetName()) + "을(를) 처치했습니다!");

		total_exp += monster->GetRewardExp();
		total_gold += monster->GetRewardGold();
		monster->SetVisible(false);
	}
}

void BattleManager::MonsterAttack()
{
	if (!player || player->IsDead()) {
		return;
	}

	for (Monster* monster : monster_list) {
		if (monster && monster->IsVisible() && !monster->IsDead()) {
			int atk = monster->GetStatus()[StatusType::Atk];
			int damage = player->TakeDamage(atk);

			UIManager::GetInstance().AddMessage(GlobalUIType::Log,
				"[피격] " + std::string(monster->GetName()) + "에게 " + std::to_string(damage) + "의 피해를 받았습니다!");

			if (player->IsDead()) {
				UIManager::GetInstance().AddMessage(GlobalUIType::Log,
					"[사망] " + std::string(monster->GetName()) + "에 의해 사망하였습니다...");
				break;
			}
		}
	}
}

bool BattleManager::IsBattleOver() const
{
	// 플레이어가 죽었거나 유효하지 않으면 true
	if (!player || player->IsDead()) {
		return true;
	}

	return IsPlayerVictory();	// 모든 몬스터가 죽은지 확인
}

bool BattleManager::IsPlayerVictory() const
{
	for (Monster* monster : monster_list) {
		if (monster && monster->IsVisible() && !monster->IsDead()) {
			return false;
		}
	}
	return true;
}

void BattleManager::DistributeReward()
{
	if (!player || player->IsDead()) {
		return;
	}

	player->GainExp(total_exp);
	player->GainGold(total_gold);

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[보상] 경험치를 " + std::to_string(total_exp) + ", 골드를 " + std::to_string(total_gold) + "획득하였습니다!");
}

int BattleManager::GetTotalExp() const
{
	return total_exp;
}

