#include "InventoryScene.h"
#include "Item.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Player.h"
#include "GameUI.h"

InventoryTab InventoryScene::next_start_tab = InventoryTab::All;

void InventoryScene::Init()
{
    ui_list[static_cast<size_t>(SceneUIType::Screen)] = std::make_unique<ScreenUI>(2, 1, 15);
    is_opaque = true;   // 불투명, 뒤의 씬이 보임

    current_tab = next_start_tab;
    next_start_tab = InventoryTab::All;

    RefreshFilter();
    SetUI();
    SetMenu();
}

void InventoryScene::SetUI()
{
    auto screen = GetLocalUI(SceneUIType::Screen);
    if (!screen) {
        return;
    }
    screen->Clear();

    // 페이지 수 계산
    // (A + B - 1) / B   <-   ceil 대신 올림 계산 
    int total_items = static_cast<int>(filtered_indices.size());
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE  - 1) / ITEMS_PER_PAGE);

    std::string header = "=== [ 인벤토리 : " + GetTabName() + " ] === (Page " +
        std::to_string(current_page + 1) + " / " + std::to_string(max_page) + ")";
    screen->AddMessage(header);
    screen->AddMessage("");

    // 현재 페이지에 해당하는 아이템만 출력
    // 마지막 아이템 인덱스는 넘어가지 않도록 min 으로 검사
    int start_idx = current_page * ITEMS_PER_PAGE;
    int end_idx = std::min(start_idx + ITEMS_PER_PAGE, total_items);

    if (total_items == 0) {
        screen->AddMessage("   인벤토리가 비어있습니다.");
    }
    else {
        for (int i = start_idx; i < end_idx; ++i) {
            int idx = filtered_indices[i];
            Item* item = player->GetInventory()[idx].get();

            std::string equip_mark = item->IsEquipped() ? "[E] " : "";

            std::string item_line = std::to_string((i - start_idx) +  1) + ". " + equip_mark + std::string(item->GetName()) +
                " (x" + std::to_string(item->GetStackCount()) + ")";
            screen->AddMessage(item_line);
        }
    }
}

void InventoryScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(GlobalUIType::Menu);
    UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "[Q/E] 탭 변경  |  [A/D] 페이지 이동  |  [0] 나가기");
    UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "사용/장착할 아이템 번호(1~8)를 누르세요: ");
}

void InventoryScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        switch (e.key_code) {
            // 탭 이동 <-
        case 'q':
        case 'Q':
            current_tab = GetPrevTab();
            RefreshFilter();
            current_page = 0;
            break;

            // 탭 이동 ->
        case 'e':
        case 'E':
            current_tab = GetNextTab();
            RefreshFilter();
            current_page = 0;
            break;


            // 페이지 이동 <-
        case 'a':
        case 'A':
            --current_page;
            break;

            // 페이지 이동 ->
        case 'd':
        case 'D':
            ++current_page;
            break;

            // 나가기
        case '0':
        case 'i':
        case 'I':
            PopScene();
            return;

            // 아이템 선택 (1 ~ 8)
        default:
            if (e.key_code >= '1' && e.key_code <= ('0' + ITEMS_PER_PAGE)) {
                int item_num = e.key_code - '1';
                size_t idx = static_cast<size_t>(current_page * ITEMS_PER_PAGE + item_num);

                // 유효한 인덱스인지 확인
                if (idx < filtered_indices.size()) {
                    size_t inven_idx = filtered_indices[idx];
                    Item* item = player->GetInventory()[inven_idx].get();

                    // 아이템 사용 (장착 토글 또는 포션 마시기)
                    bool is_used = item->Use(player);

                    // 포션 등을 마셔서 소모되었다면 수량 감소 및 삭제 처리
                    if (is_used) {
                        if (item->GetStackCount() <= 0) {
                            player->RemoveItem(inven_idx);
                            RefreshFilter(); // 아이템이 지워졌으니 필터 재계산
                        }
                    }
                }
            }
            break;
        }

        CheckPage();
        SetUI();
    }
}

void InventoryScene::Update(float delta_time)
{
}

void InventoryScene::Render()
{
}

void InventoryScene::Release()
{
}


// private 함수
// 탭 변경 시 아이템 필터링
void InventoryScene::RefreshFilter()
{
    filtered_indices.clear();
    const auto& inventory = player->GetInventory();
    filtered_indices.reserve(inventory.size());

    for (size_t i = 0; i < inventory.size(); ++i) {
        Item* item = inventory[i].get();
        if (!item) {
            continue;
        }

        bool is_match = false;
        switch (current_tab) {
        case InventoryTab::All:        is_match = true; break;
        case InventoryTab::Equipment:  is_match = (item->GetType() == ItemType::Equipment); break;
        case InventoryTab::Consumable: is_match = (item->GetType() == ItemType::Potion); break;
        case InventoryTab::Junk:       is_match = (item->GetType() == ItemType::Junk); break;
        default: break;
        }

        if (is_match) {
            filtered_indices.push_back(i);
        }
    }
}

void InventoryScene::CheckPage()
{
    int total_items = static_cast<int>(filtered_indices.size());
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);

    if (current_page < 0) {
        current_page = 0;
    }
    if (current_page >= max_page) {
        current_page = max_page - 1;
    }
}

std::string InventoryScene::GetTabName() const
{
    switch (current_tab) {
    case InventoryTab::All: return "전체";
    case InventoryTab::Equipment: return "장비";
    case InventoryTab::Consumable: return "소모품";
    case InventoryTab::Junk: return "잡템";
    }
    return "";
}

InventoryTab InventoryScene::GetNextTab()
{
    int next = static_cast<int>(current_tab) + 1;
    if (next >= static_cast<int>(InventoryTab::COUNT)) {
        next = 0;
    }
    return static_cast<InventoryTab>(next);
}

InventoryTab InventoryScene::GetPrevTab()
{
    int prev = static_cast<int>(current_tab) - 1;
    if (prev < 0) {
        prev = static_cast<int>(InventoryTab::COUNT) - 1;
    }
    return static_cast<InventoryTab>(prev);
}
