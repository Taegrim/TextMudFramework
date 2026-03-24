#pragma once
#include "BattleEntity.h"

class Item;
class Equipment;

class Player : public BattleEntity
{
public:
	Player(std::string_view name, std::string_view img, const Status& stat);

	void Render() override;

	// 스탯 관련
	void Heal(int amount);
	void MaxHeal();
	
	// 아이템
	void AddItem(std::unique_ptr<Item> new_item);
	void RemoveItem(size_t index);
	const std::vector<std::unique_ptr<Item>>& GetInventory() const;

	// 장비
	void Equip(Equipment* equipment);
	void UnEquip(EquipmentSlot slot);
	Equipment* GetEquippedItem(EquipmentSlot slot) const;

	// 경험치, 골드
	void GainExp(unsigned int amount);
	void GainGold(unsigned int amount);
	void SpendGold(unsigned int amount);

	unsigned int GetLevel() const;
	unsigned int GetExp() const;
	unsigned int GetGold() const;
	int GetHp() const;

private:
	unsigned int level = 1;
	unsigned int exp = 0;
	unsigned int gold = 0;
	std::vector<std::unique_ptr<Item>> inventory;	// 인벤토리 가방
	std::array<Equipment*, static_cast<int>(EquipmentSlot::COUNT)> equipment_slots;	// 장비슬롯

	unsigned int GetRequiredExp() const;
};

