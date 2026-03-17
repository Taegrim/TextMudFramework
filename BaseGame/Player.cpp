#include "Player.h"

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
}
