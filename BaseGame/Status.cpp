#include "Status.h"

Status::Status()
{
	status.fill(0);
}

int Status::TakeDamage(int dmg)
{
	int total_damage = std::max(1, dmg - GetStatus(StatusType::Def));
	
	(*this)[StatusType::Hp] -= total_damage;
	if ((*this)[StatusType::Hp] <= 0) {
		(*this)[StatusType::Hp] = 0;
	}

	return total_damage;
}

bool Status::IsDead() const
{
	return GetStatus(StatusType::Hp) <= 0;
}

int Status::GetStatus(StatusType type) const
{
	// 자주 사용될 수 있으므로 if 대신 assert로 디버그 모드에서만 문제 확인

	// Release 에선 무시됨
	assert(static_cast<int>(type) >= 0 && 
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	return status[static_cast<int>(type)];
}

int Status::GetHp() const
{
	return GetStatus(StatusType::Hp);
}

void Status::SetStatus(StatusType type, int value)
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	status[static_cast<int>(type)] = value;
}

void Status::SetHp(int value)
{
	SetStatus(StatusType::Hp, value);
}
