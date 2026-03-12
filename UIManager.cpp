#include "UIManager.h"

UIManager::UIManager() 
{
    // 0: Screen (x:2, y:2, 15줄)
    ui_list.push_back(new ScreenUI(2, 2, 15));

    // 1: Log (x:62, y:1, 15줄)
    ui_list.push_back(new LogUI(62, 1, 15));

    // 2: Minimap (x:2, y:2, 5줄) -> 덮어쓰기
    ui_list.push_back(new MinimapUI(2, 2, 5));

    // 3: Character (x:30, y:2, 5줄) -> 덮어쓰기
    ui_list.push_back(new CharacterUI(30, 2, 5));

    // 4: Message (x:0, y:21, 3줄)
    ui_list.push_back(new MessageUI(0, 21, 3));
}

UIManager::~UIManager()
{
    for (BaseUI* ui : ui_list) {
        if (ui) {
            delete ui;
        }
    }
    ui_list.clear();
}


// ----------------------------------------------------
// 데이터 조작 함수
// ----------------------------------------------------
void UIManager::AddMessage(UIType type, const std::string& msg) 
{
    int idx = static_cast<int>(type);

    if (idx >= 0 && idx < static_cast<int>(UIType::COUNT)) {
        ui_list[idx]->AddMessage(msg);
    }
}

// ----------------------------------------------------
// 그리기 함수들 (순서대로 호출됨)
// ----------------------------------------------------
void UIManager::Render() 
{
    for (const auto& ui : ui_list) {
        if (ui->IsValid()) {
            ui->Render();
        }
    }
}