#include "Item.h"
#include "UIManager.h"
#include "Player.h"
#include <cassert>


Item::Item(std::string_view n, std::string_view desc, int price, ItemType type)
	: name(n), description(desc), price(price), type(type)
{
}

std::string_view Item::GetName() const
{
	return name;
}

std::string_view Item::GetDesc() const
{
	return description;
}

int Item::GetPrice() const
{
	return price;
}

ItemType Item::GetType() const
{
	return type;
}



// 장비
Equipment::Equipment(std::string_view n, std::string_view desc,  int price, EquipmentSlot slot,  bool is_equipped)
	: Item(n, desc, price, ItemType::Equipment), slot(slot), is_equipped(is_equipped)
{
}

void Equipment::Use(Player* player)
{
	if (!player) {
		return;
	}

	if (IsEquipped()) {
		player->UnEquip(slot);
	}
	else {
		player->Equip(this);
	}
}

EquipmentSlot Equipment::GetSlot() const
{
	return slot;
}

bool Equipment::IsEquipped() const
{
	return is_equipped;
}

const std::vector<std::pair<StatusType, int>>& Equipment::GetBonusStat() const
{
	return bonus_stat;
}

void Equipment::SetEquipped(bool val)
{
	is_equipped = val;
}

void Equipment::SetBonusStat(const std::vector<std::pair<StatusType, int>>& stats)
{
	bonus_stat = stats;
}



// 소모품
Consumable::Consumable(std::string_view n, std::string_view desc, int price, int amount)
	: Item(n, desc, price, ItemType::Potion), amount(amount)
{
}

void Consumable::Use(Player* player)
{
	if (!player) {
		return;
	}

	player->Heal(amount);
}

int Consumable::GetAmount() const
{
	return amount;
}

JunkItem::JunkItem(std::string_view n, std::string_view desc, int price)
	: Item(n, desc, price, ItemType::Junk)
{
}

void JunkItem::Use(Player* player)
{
	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[에러] 이 아이템은 사용할 수 없습니다. 상점에 판매하세요.");

	assert(false && "잡템의 Use 함수가 호출되었습니다!");
}
