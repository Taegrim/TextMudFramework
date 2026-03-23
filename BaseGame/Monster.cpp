#include "Monster.h"
#include "ItemManager.h"

Monster::Monster() : BattleEntity("None", " ", Status()), reward_gold(0), reward_exp(0)
{
	is_visible = false;
}

Monster::Monster(std::string_view name, std::string_view img, const Status& stat, int gold, int exp) :
	BattleEntity(name, img, stat), reward_gold(gold), reward_exp(exp)
{
}

void Monster::Render()
{
	if (!is_visible) {
		return;
	}

	// ·»´õ¸µ
}

void Monster::Spawn(std::string_view name, std::string_view img, const Status& stat, int gold, int exp)
{
	this->name = name;
	this->image = img;
	this->status = stat;
	this->reward_gold = gold;
	this->reward_exp = exp;
	this->is_visible = true;

	drop_table = nullptr;
}

void Monster::SetDropTable(const DropTable* table)
{
	drop_table = table;
}

std::vector<std::unique_ptr<Item>> Monster::CheckDrops() const
{
	std::vector<std::unique_ptr<Item>> items;

	if (drop_table) {
		for (const auto& table : *drop_table) {
			if (RandomUtil::GetRange(1, 100) <= table.rate) {
				auto item = ItemManager::GetInstance().CreateItem(table.item_id);

				if (item) {
					items.push_back(std::move(item));
				}
			}
		}
	}

	return items;
}

int Monster::GetRewardExp() const
{
	return reward_exp;
}

int Monster::GetRewardGold() const
{
	return reward_gold;
}
