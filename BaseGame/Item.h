#pragma once
#include "common.h"

constexpr int MAX_STACK_COUNT = 99;
class Player;

class Item
{
public:
	Item(std::string_view n, std::string_view desc, int price, ItemType type, int count = 1, int max_stack = MAX_STACK_COUNT);
	virtual ~Item() = default;

	virtual bool Use(Player* player) = 0;	// 사용 성공 true, 사용 실패 false
	virtual bool IsEquipped() const;		// 기본적으로 false, 장비만 true

	std::string_view GetName() const;
	std::string_view GetDesc() const;
	int GetPrice() const;
	ItemType GetType() const;
	int GetStackCount() const;
	int GetMaxStack() const;

	void SetStackCount(int amount);
	void AddStackCount(int amount);

protected:
	std::string name;
	std::string description;
	int price;
	ItemType type;
	int stack_count;		// 현재 소지량
	int max_stack;			// 최대 소지량
};

class Equipment : public Item
{
public:
	Equipment(std::string_view n, std::string_view desc, int price, EquipmentSlot slot, bool is_equipped = false);

	bool Use(Player* player) override;
	
	EquipmentSlot GetSlot() const;
	bool IsEquipped() const override;
	const std::vector<std::pair<StatusType, int>>& GetBonusStat() const;
	
	void SetEquipped(bool val);
	void SetBonusStat(const std::vector<std::pair<StatusType, int>>& stats);

private:
	EquipmentSlot slot;
	std::vector<std::pair<StatusType, int>> bonus_stat;
	bool is_equipped;
};

class Consumable : public Item
{
public:
	Consumable(std::string_view n, std::string_view desc, int price, int amount, int count = 1);

	bool Use(Player* player) override;
	
	int GetAmount() const;

private:
	int amount;		// 회복량
};

class JunkItem : public Item
{
public:
	JunkItem(std::string_view n, std::string_view desc, int price, int count = 1);

	bool Use(Player* player) override;
};
