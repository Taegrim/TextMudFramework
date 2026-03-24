#pragma once
#include "BaseScene.h"
#include <vector>

enum class InventoryTab {
    All,
    Equipment,
    Consumable,
    Junk,
    COUNT
};

class InventoryScene : public BaseScene
{
public:
    InventoryScene() = default;

    void Init() override;
    void SetUI() override;
    void SetMenu() override;
    void ProcessEvent(const Event& e) override;
    void Update(float delta_time) override;
    void Render() override;
    void Release() override;

    static InventoryTab next_start_tab;

private:
    InventoryTab current_tab;
    int current_page = 0;
    const int ITEMS_PER_PAGE = 8;
    std::vector<size_t> filtered_indices;   // 아이템들의 인벤토리 원본 인덱스를 모아두는 배열


    void RefreshFilter(); // 탭이 바뀔 때마다 필터링 목록 갱신
    void CheckPage();
    std::string GetTabName() const;
    InventoryTab GetNextTab();
    InventoryTab GetPrevTab();
};