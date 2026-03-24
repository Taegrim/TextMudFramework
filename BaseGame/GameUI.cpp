#include "GameUI.h"
#include "RenderSystem.h"

ScreenUI::ScreenUI(int x, int y, unsigned int lines) : BaseUI(x, y, lines)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines) - 3);
}

void ScreenUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y,
        "========================================");
    RenderSystem::GetInstance().PrintText(start_x, start_y + 1,
        "           [ 메인 뷰포트 ]              ");

    // 임시 내용
    for (size_t i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 2 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines,
        "========================================");
}

MessageUI::MessageUI(int x, int y, unsigned int lines) : BaseUI(x, y, lines)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines) - 1);
}

void MessageUI::Render()
{
    RenderSystem::GetInstance().PrintText(start_x, start_y,
        "------------------------------------------------------------");

    for (size_t i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i, 
            "[알림] " + messages[i]);
    }
}

LogUI::LogUI(int x, int y, unsigned int lines) : BaseUI(x, y, lines)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines) - 1);
}

void LogUI::Render()
{
    RenderSystem::GetInstance().PrintText(start_x, start_y, "[ 전투 / 행동 로그 ]");

    for (size_t i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + 1 + i,
            messages[i]);
    }
}

MinimapUI::MinimapUI(int x, int y, unsigned int lines) : BaseUI(x, y, lines)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines) - 3);
}

void MinimapUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y, "+--------+");
    RenderSystem::GetInstance().PrintText(start_x, start_y + 1, "| MINIMAP|");
    
    for (size_t i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 2 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines, "+--------+");
}

CharacterUI::CharacterUI(int x, int y, unsigned int lines) : BaseUI(x, y, lines)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines) - 2);
}

void CharacterUI::Render()
{
    // 상단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y, "+------------+");

    for (size_t i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i, messages[i]);
    }

    // 하단 테두리
    RenderSystem::GetInstance().PrintText(start_x, start_y + max_lines - 1, "+------------+");
}
