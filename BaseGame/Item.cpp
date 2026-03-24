#include "Item.h"
#include "UIManager.h"
#include "Player.h"
#include <cassert>


Item::Item(std::string_view n, std::string_view desc, int price, ItemType type, int count, int max_stack)
	: name(n), description(desc), price(price), type(type), stack_count(count), max_stack(max_stack)
{
}

bool Item::IsEquipped() const
{
	return false;
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

int Item::GetStackCount() const
{
	return stack_count;
}

int Item::GetMaxStack() const
{
	return max_stack;
}

void Item::SetStackCount(int amount)
{
	stack_count = amount;
}

void Item::AddStackCount(int amount)
{
	stack_count += amount;
}



// 장비
Equipment::Equipment(std::string_view n, std::string_view desc,  int price, EquipmentSlot slot,  bool is_equipped)
	: Item(n, desc, price, ItemType::Equipment, 1, 1), slot(slot), is_equipped(is_equipped)
{
}

bool Equipment::Use(Player* player)
{
	if (!player) {
		return false;
	}

	if (IsEquipped()) {
		player->UnEquip(slot);
	}
	else {
		player->Equip(this);
	}
	return true;
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
Consumable::Consumable(std::string_view n, std::string_view desc, int price, int amount, int count)
	: Item(n, desc, price, ItemType::Potion, count, MAX_STACK_COUNT), amount(amount)
{
}

bool Consumable::Use(Player* player)
{
	if (!player) {
		return false;
	}

	if (stack_count <= 0) {
		return false;
	}

	if (player->GetHp() >= player->GetStatus()[StatusType::MaxHp]) {
		UIManager::GetInstance().AddMessage(GlobalUIType::Log, "체력이 이미 가득 차 있습니다.");
		return false;
	}

	player->Heal(amount);
	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[회복] " + name + "을(를) 사용하여 체력을 " + std::to_string(amount) + " 회복했습니다.");
	--stack_count;
	return true;
}

int Consumable::GetAmount() const
{
	return amount;
}

JunkItem::JunkItem(std::string_view n, std::string_view desc, int price, int count)
	: Item(n, desc, price, ItemType::Junk, count, MAX_STACK_COUNT)
{
}

bool JunkItem::Use(Player* player)
{
	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"이 아이템은 사용할 수 없습니다. 상점에 판매하세요.");

	return false;
}
