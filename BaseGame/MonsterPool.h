#pragma once
#include "common.h"
#include "Monster.h"

class MonsterPool
{
public:
	static MonsterPool& GetInstance() {
		static MonsterPool instance;
		return instance;
	}

	// 복사 생성자와 대입 연산자 삭제
	MonsterPool(const MonsterPool&) = delete;
	MonsterPool& operator=(const MonsterPool&) = delete;

	void Init(int capacity = 20);

	Monster* SpawnRandomMonster();
	Monster* SpawnMonster(MonsterType type);

private:
	std::vector<std::unique_ptr<Monster>> pool;

	MonsterPool();
	~MonsterPool();
};

