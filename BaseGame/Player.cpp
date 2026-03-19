#include "Player.h"
#include "UIManager.h"

Player::Player(std::string_view name, std::string_view img, const Status& stat)
	: BattleEntity(name, img, stat)
{
}

void Player::Render()
{
	// 렌더링
}

void Player::GainExp(int amount)
{
	exp += amount;

	// 레벨업 처리
	while (exp >= GetRequiredExp()) {
		exp -= GetRequiredExp();
		++level;

		status[StatusType::MaxHp] += 20;
		status[StatusType::Atk] += 2;
		status[StatusType::Def] += 1;

		MaxHeal();

		UIManager::GetInstance().AddMessage(GlobalUIType::Log,
			"[레벨업] " + std::string(GetName()) + "의 레벨이 " + std::to_string(level) + "로 상승하였습니다!");
	}
}

void Player::GainGold(int amount)
{
	gold += amount;
}

void Player::Heal(int amount)
{
	int value = status[StatusType::Hp] + amount;
	if (value >= status[StatusType::MaxHp]) {
		value = status[StatusType::MaxHp];
	}
	status[StatusType::Hp] = value;
}

void Player::MaxHeal()
{
	status[StatusType::Hp] = status[StatusType::MaxHp];
}

int Player::GetLevel() const
{
	return level;
}

int Player::GetExp() const
{
	return exp;
}

int Player::GetGold() const
{
	return gold;
}


// private 함수
// 경험치 요구랑
int Player::GetRequiredExp() const
{
	return level * 50;
}
