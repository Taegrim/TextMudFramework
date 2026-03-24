#pragma once
#include "common.h"

class ItemManager
{
public:
    static ItemManager& GetInstance() {
        static ItemManager instance;
        return instance;
    }

    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;

    // 드롭 테이블 생성
    void Init();

    // 몬스터 이름으로 드롭 테이블 주소 반환
    const DropTable* GetDropTable(const std::string& name) const;

    // item_id 로 아이템 생성
    std::unique_ptr<Item> CreateItem(int item_id);

private:
    std::unordered_map<std::string, DropTable> drop_tables;

    ItemManager() = default;
    ~ItemManager() = default;
};

