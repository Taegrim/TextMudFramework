#pragma once
#include "common.h"

class Player;

class Item
{
public:
	Item(std::string_view n, std::string_view desc, int price, ItemType type);
	virtual ~Item() = default;

	virtual void Use(Player* player) = 0;

	std::string_view GetName() const;
	std::string_view GetDesc() const;
	int GetPrice() const;
	ItemType GetType() const;

protected:
	std::string name;
	std::string description;
	int price;
	ItemType type;
};

class Equipment : public Item
{
public:
	Equipment(std::string_view n, std::string_view desc, int price, EquipmentSlot slot, bool is_equipped = false);

	void Use(Player* player) override;
	
	EquipmentSlot GetSlot() const;
	bool IsEquipped() const;
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
	Consumable(std::string_view n, std::string_view desc, int price, int amount);

	void Use(Player* player) override;
	
	int GetAmount() const;

private:
	int amount;
};

class JunkItem : public Item
{
public:
	JunkItem(std::string_view n, std::string_view desc, int price);

	void Use(Player* player) override;
};
