#include "Status.h"

// 데미지 난수 범위 90~110
constexpr int MIN_RATE = 90;
constexpr int MAX_RATE = 110;

Status::Status()
{
	status.fill(0);
	bonus_status.fill(0);
}

int Status::TakeDamage(int dmg)
{
	int base_damage = std::max(1, dmg - (*this)[StatusType::Def]);
	int rate = RandomUtil::GetRange(MIN_RATE, MAX_RATE);

	int total_damage = (base_damage * rate) / 100;
	total_damage = std::max(1, total_damage);

	status[static_cast<int>(StatusType::Hp)] -= total_damage;
	if (status[static_cast<int>(StatusType::Hp)] <= 0) {
		status[static_cast<int>(StatusType::Hp)] = 0;
	}

	return total_damage;
}

bool Status::IsDead() const
{
	return (*this)[StatusType::Hp] <= 0;
}

void Status::Heal(int amount)
{
	if (amount <= 0) {
		return;
	}

	int max_hp = (*this)[StatusType::MaxHp];
	int hp = GetHp();
	
	hp += amount;
	if (hp >= max_hp) {
		hp = max_hp;
	}

	status[static_cast<int>(StatusType::Hp)] = hp;
}

void Status::MaxHeal()
{
	status[static_cast<int>(StatusType::Hp)] = (*this)[StatusType::MaxHp];
}

void Status::AddStatus(StatusType type, int amount)
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	status[static_cast<int>(type)] += amount;
}

void Status::AddBonus(StatusType type, int amount)
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	bonus_status[static_cast<int>(type)] += amount;
}

void Status::RemoveBonus(StatusType type, int amount)
{
	AddBonus(type, -amount);
}

int Status::GetStatus(StatusType type) const
{
	// 자주 사용될 수 있으므로 if 대신 assert로 디버그 모드에서만 문제 확인
	// Release 에선 무시됨
	assert(static_cast<int>(type) >= 0 && 
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	return status[static_cast<int>(type)];
}

int Status::GetTotal(StatusType type) const
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	return status[static_cast<int>(type)] + bonus_status[static_cast<int>(type)];
}

int Status::GetHp() const
{
	return status[static_cast<int>(StatusType::Hp)];
}

void Status::SetStatus(StatusType type, int value)
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	status[static_cast<int>(type)] = value;
}
