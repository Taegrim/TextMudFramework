#include "MonsterPool.h"
#include "Item.h"
#include "ItemManager.h"

MonsterPool::MonsterPool()
{
}

MonsterPool::~MonsterPool()
{
}

void MonsterPool::Init(size_t capacity)
{
	pool.reserve(capacity);

	for (size_t i = 0; i < capacity; ++i) {
		pool.push_back(std::make_unique<Monster>());
	}
}

Monster* MonsterPool::SpawnRandomMonster()
{
	MonsterType type = static_cast<MonsterType>(RandomUtil::GetRange(0, static_cast<int>(MonsterType::None) - 1));
	return SpawnMonster(type);
}

Monster* MonsterPool::SpawnMonster(MonsterType type)
{
	if (type == MonsterType::None) {
		return nullptr;
	}

	Monster* monster = nullptr;

	// 유휴 몬스터 찾기
	for (auto& m : pool) {
		if (!m->IsVisible()) {
			monster = m.get();
			break;
		}
	}
	// 몬스터 풀이 꽉 참
	if (!monster) {
		return monster;
	}

	auto& item_manager = ItemManager::GetInstance();
	switch (type) {
	case MonsterType::Slime:
		monster->Spawn("슬라임", "S", Status(30, 30, 0, 0, 5, 2), 10, 5);
		monster->SetDropTable(item_manager.GetDropTable("슬라임"));
		break;
	case MonsterType::Goblin:
		monster->Spawn("고블린", "G", Status(50, 50, 0, 0, 12, 5), 25, 15);
		monster->SetDropTable(item_manager.GetDropTable("고블린"));
		break;
	default:
		return nullptr;
	}

	return monster;
}
