#pragma once
#include "common.h"

class Status
{
public:
	Status();
	
	// 2. C++17 가변 인자 템플릿 생성자
	template <typename... Args>
	Status(Args... args) : status{ static_cast<int>(args)... }{}
	
	~Status() = default;


	// 스탯 관련 로직
	void TakeDamage(int dmg);
	bool IsDead() const;

	int& operator[](StatusType type) {
		assert(static_cast<int>(type) >= 0 &&
			static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

		return status[static_cast<int>(type)];
	}
	const int& operator[](StatusType type) const {
		assert(static_cast<int>(type) >= 0 &&
			static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

		return status[static_cast<int>(type)];
	}

	// 게터, 세터, 스탯 확인
	int GetStatus(StatusType type) const;
	int GetHp() const;

	void SetStatus(StatusType type, int value);
	void SetHp(int value);

	void ShowStatus();

private:
	std::array<int, static_cast<int>(StatusType::COUNT)> status;
};

