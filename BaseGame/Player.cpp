#include "Player.h"
#include "UIManager.h"
#include "Item.h"

Player::Player(std::string_view name, std::string_view img, const Status& stat)
	: BattleEntity(name, img, stat)
{
	equipment_slots.fill(nullptr);
}

void Player::Render()
{
	// 렌더링
}

void Player::Heal(int amount)
{
	status.Heal(amount);
}

void Player::MaxHeal()
{
	status.MaxHeal();
}

void Player::AddItem(std::unique_ptr<Item> item)
{
	if (!item) {
		return;
	}

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[획득] " + std::string(item->GetName()) + "을(를) 획득했습니다.");

	inventory.push_back(std::move(item));
}

void Player::RemoveItem(int index)
{
	if (index < 0 || index >= inventory.size()) {
		return;
	}

	Item* item = inventory[index].get();

	// 버릴 아이템이 장비라면 먼저 벗기고 삭제
	if (item->GetType() == ItemType::Equipment) {
		Equipment* e = static_cast<Equipment*>(item);
		if (e->IsEquipped()) {
			UnEquip(e->GetSlot());
		}
	}

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[버림] " + std::string(item->GetName()) + "을(를) 버렸습니다.");

	inventory.erase(inventory.begin() + index);
}

const std::vector<std::unique_ptr<Item>>& Player::GetInventory() const
{
	return inventory;
}

void Player::Equip(Equipment* equipment)
{
	if (!equipment) {
		return;
	}

	int slot = static_cast<int>(equipment->GetSlot());

	// 기존 장착한 장비가 있다면 벗김
	if (equipment_slots[slot]) {
		UnEquip(equipment->GetSlot());
	}

	// 기존에 최대 체력인지 확인
	bool was_max_hp = (GetHp() == status[StatusType::MaxHp]);

	// 장비 장착
	equipment_slots[slot] = equipment;
	equipment->SetEquipped(true);

	// 장비 효과 적용
	auto& stats = equipment->GetBonusStat();
	for (const auto& [type, value] : stats) {
		status.AddBonus(type, value);
	}
	
	// 기존에 최대 체력이었다면 장비를 착용해도 풀피 유지
	if (was_max_hp) {
		MaxHeal();
	}

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[장착] " + std::string(equipment->GetName()) + "을(를) 장착했습니다.");
}

void Player::UnEquip(EquipmentSlot slot)
{
	int idx = static_cast<int>(slot);
	Equipment* e = equipment_slots[idx];

	if (!e) {
		return;
	}

	// 장비 효과 해제
	auto& stats = e->GetBonusStat();
	for (const auto& [type, value] : stats) {
		status.RemoveBonus(type, value);
	}

	// 장비 해제 시 체력 체크
	if (status[StatusType::Hp] >= status[StatusType::MaxHp]) {
		status.SetStatus(StatusType::Hp, status[StatusType::MaxHp]);
	}

	// 장비 해제
	e->SetEquipped(false);
	equipment_slots[idx] = nullptr;

	UIManager::GetInstance().AddMessage(GlobalUIType::Log,
		"[해제] " + std::string(e->GetName()) + "을(를) 해제했습니다.");
}

Equipment* Player::GetEquippedItem(EquipmentSlot slot) const
{
	return equipment_slots[static_cast<int>(slot)];
}

void Player::GainExp(int amount)
{
	exp += amount;

	// 레벨업 처리
	while (exp >= GetRequiredExp()) {
		exp -= GetRequiredExp();
		++level;

		status.AddStatus(StatusType::MaxHp, 20);
		status.AddStatus(StatusType::Atk, 2);
		status.AddStatus(StatusType::Def, 1);

		MaxHeal();

		UIManager::GetInstance().AddMessage(GlobalUIType::Log,
			"[레벨업] " + std::string(GetName()) + "의 레벨이 " + std::to_string(level) + "로 상승하였습니다!");
	}
}

void Player::GainGold(int amount)
{
	gold += amount;
}

void Player::SpendGold(int amount)
{
	gold -= amount;
}

int Player::GetLevel() const
{
	return level;
}

int Player::GetExp() const
{
	return exp;
}

int Player::GetGold() const
{
	return gold;
}

int Player::GetHp() const
{
	return status.GetHp();
}

// private 함수
// 경험치 요구랑
int Player::GetRequiredExp() const
{
	return level * 50;
}
