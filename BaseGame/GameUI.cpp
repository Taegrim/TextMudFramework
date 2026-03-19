#include "GameUI.h"
#include "RenderSystem.h"

void ScreenUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y,
        "========================================");
    RenderSystem::GetInstance().PrintText(start_x, start_y + 1,
        "           [ 메인 뷰포트 ]              ");

    // 임시 내용
    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 7 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines,
        "========================================");
}

void MessageUI::Render()
{
    RenderSystem::GetInstance().PrintText(start_x, start_y,
        "------------------------------------------------------------");

    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i, 
            "[알림] " + messages[i]);
    }
}

void LogUI::Render()
{
    RenderSystem::GetInstance().PrintText(start_x, start_y, "[ 전투 / 행동 로그 ]");

    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + 1 + i,
            messages[i]);
    }
}

void MinimapUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y, "+--------+");
    RenderSystem::GetInstance().PrintText(start_x, start_y + 1, "| MINIMAP|");
    
    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 2 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines, "+--------+");
}

void CharacterUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y, "+------------+");

    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines - 1, "+------------+");
}
