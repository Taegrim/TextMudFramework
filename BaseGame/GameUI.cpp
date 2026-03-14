#include "GameUI.h"

void ScreenUI::Render()
{
    UIManager::GetInstance().PrintText(start_x, start_y,
        "========================================");


    UIManager::GetInstance().PrintText(start_x, start_y + 1,
        "           [ 메인 뷰포트 ]              ");


    UIManager::GetInstance().PrintText(start_x, start_y + max_lines,
        "========================================");
}

void MessageUI::Render()
{
    UIManager::GetInstance().PrintText(start_x, start_y,
        "------------------------------------------------------------");

    for (int i = 0; i < messages.size(); ++i) {
        UIManager::GetInstance().PrintText(start_x + 2, start_y + 1 + i, 
            { "[알림] " + messages[i] });
    }
}

void LogUI::Render()
{
    UIManager::GetInstance().PrintText(start_x, start_y, "[ 전투 / 행동 로그 ]");

    for (int i = 0; i < messages.size(); ++i) {
        UIManager::GetInstance().PrintText(start_x, start_y + 1 + i,
            messages[i]);
    }
}

void MinimapUI::Render()
{
    UIManager::GetInstance().PrintText(start_x, start_y, "+--------+");

    UIManager::GetInstance().PrintText(start_x, start_y + 1, "| MINIMAP|");
    UIManager::GetInstance().PrintText(start_x, start_y + 2, "|   @    |");

    UIManager::GetInstance().PrintText(start_x, start_y + 3, "+--------+");
}

void CharacterUI::Render()
{
    UIManager::GetInstance().PrintText(start_x, start_y, "+------------+");
    UIManager::GetInstance().PrintText(start_x, start_y + 1, "| LV: 5      |");
    UIManager::GetInstance().PrintText(start_x, start_y + 2, "| HP: 100/100|");
    UIManager::GetInstance().PrintText(start_x, start_y + 3, "| MP: 50/50  |");
    UIManager::GetInstance().PrintText(start_x, start_y + 4, "+------------+");
}
