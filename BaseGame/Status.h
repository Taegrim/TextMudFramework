#pragma once
#include "common.h"

class Status
{
public:
	Status();
	
	// C++17 가변 인자 템플릿 생성자
	template <typename... Args>
	Status(Args... args) : status{ static_cast<int>(args)... }{
		static_assert(sizeof...(Args) == static_cast<size_t>(StatusType::COUNT), "스탯 개수가 일치하지 않습니다.");
	}
	
	~Status() = default;

	int operator[](StatusType type) const {
		return GetTotal(type);
	}


	// 스탯 관련 로직
	int TakeDamage(int dmg);	// 데미지 처리
	bool IsDead() const;
	void Heal(int amount);
	void MaxHeal();
	void AddStatus(StatusType type, int amount);

	// 보너스 스탯 처리
	void AddBonus(StatusType type, int amount);
	void RemoveBonus(StatusType type, int amount);

	// 게터, 세터
	int GetStatus(StatusType type) const;
	int GetTotal(StatusType type) const;
	int GetHp() const;

	void SetStatus(StatusType type, int value);

private:
	std::array<int, static_cast<int>(StatusType::COUNT)> status;			// 기본 스탯
	std::array<int, static_cast<int>(StatusType::COUNT)> bonus_status{ 0 };	// 장비 보너스 스탯
};

