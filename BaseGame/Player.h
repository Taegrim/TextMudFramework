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
	void AddItem(std::unique_ptr<Item> item);
	void RemoveItem(int index);
	const std::vector<std::unique_ptr<Item>>& GetInventory() const;

	// 장비
	void Equip(Equipment* equipment);
	void UnEquip(EquipmentSlot slot);
	Equipment* GetEquippedItem(EquipmentSlot slot) const;

	// 경험치, 골드
	void GainExp(int amount);
	void GainGold(int amount);
	void SpendGold(int amount);

	int GetLevel() const;
	int GetExp() const;
	int GetGold() const;
	int GetHp() const;

private:
	int level = 1;
	int exp = 0;
	int gold = 0;
	std::vector<std::unique_ptr<Item>> inventory;	// 인벤토리 가방
	std::array<Equipment*, static_cast<int>(EquipmentSlot::COUNT)> equipment_slots;	// 장비슬롯

	int GetRequiredExp() const;
};

