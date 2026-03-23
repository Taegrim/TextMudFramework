#include "ItemManager.h"
#include "Item.h"

void ItemManager::Init()
{
    // 잡템 1XXX, 장비 2XXX, 소모품 3XXX
    drop_tables["슬라임"] = { {40, 1001} };
    drop_tables["고블린"] = { {30, 1002}, {5, 2001} };
}

std::unique_ptr<Item> ItemManager::CreateItem(int item_id)
{
    switch (item_id) {
    case 1001: // 슬라임 전리품
        return std::make_unique<JunkItem>("미끈미끈한 액체", "슬라임의 체액", 5);

    case 1002: // 고블린 전리품
        return std::make_unique<JunkItem>("고블린의 뼛조각", "고블린의 유해", 10);

    case 2001: // 고블린 장비
    {
        auto club = std::make_unique<Equipment>("고블린의 몽둥이", "고블린이 사용하던 몽둥이", 40, EquipmentSlot::Weapon);
        club->SetBonusStat({ { StatusType::Atk, 5 } });
        return club;
    }

    default:
        return nullptr; // 없는 아이템 ID
    }
}

const DropTable* ItemManager::GetDropTable(std::string_view name) const
{
    auto it = drop_tables.find(std::string(name));
    if (it != drop_tables.end()) {
        return &it->second;
    }
    return nullptr;
}
