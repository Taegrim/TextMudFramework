#include "UIManager.h"
#include "RenderSystem.h"

UIManager::UIManager()
{
    // UI : x, y, max_line
    // Log (x:62, y:1, 15줄)
    ui_list.push_back(std::make_unique<LogUI>(62, 1, 15));

    // Message (x:0, y:21, 4줄)
    ui_list.push_back(std::make_unique<MessageUI>(0, 21, 4));
}

UIManager::~UIManager()
{
}

void UIManager::AddMessage(GlobalUIType type, std::string_view msg)
{
    int idx = static_cast<int>(type);

    if (idx >= 0 && idx < static_cast<int>(GlobalUIType::COUNT)) {
        ui_list[idx]->AddMessage(msg);
    }
}

void UIManager::ClearMessage(GlobalUIType type)
{
    int idx = static_cast<int>(type);

    if (idx >= 0 && idx < static_cast<int>(GlobalUIType::COUNT)) {
        ui_list[idx]->Clear();
    }
}

void UIManager::ClearAll(const std::vector<GlobalUIType>& ignore_list)
{
    for (int i = 0; i < static_cast<int>(GlobalUIType::COUNT); ++i) {
        GlobalUIType current_type = static_cast<GlobalUIType>(i);

        auto it = std::find(ignore_list.begin(), ignore_list.end(), current_type);
        if (it != ignore_list.end()) {
            continue;
        }

        ui_list[i]->Clear();
    }
}

void UIManager::Render()
{
    // 로그ui, 메세지ui 등 전역 ui 그리기
    for (const auto& ui : ui_list) {
        if (ui->IsVisible()) {
            ui->Render();
        }
    }
}

void UIManager::SetVisible(GlobalUIType type, bool value)
{
    int idx = static_cast<int>(type);
    if (idx >= 0 && idx < static_cast<int>(GlobalUIType::COUNT)) {
        ui_list[idx]->SetVisible(value);
    }
}

void UIManager::SetAllVisible(bool value)
{
    for (auto& ui : ui_list) {
        ui->SetVisible(value);
    }
}
