#include "GameUI.h"


void ScreenUI::Render()
{
    Gotoxy(start_x, start_y);
    std::cout << "========================================";


    Gotoxy(start_x, start_y + 1);  
    std::cout << "           [ 메인 뷰포트 ]              ";


    Gotoxy(start_x, start_y + 20); 
    std::cout << "========================================";
}

void MessageUI::Render()
{
    Gotoxy(start_x, start_y);
    std::cout << "------------------------------------------------------------";

    for (size_t i = 0; i < messages.size(); ++i) {
        Gotoxy(start_x + 2, start_y + 1 + i);
        std::cout << "[알림] " << messages[i] << "                              ";
    }

    Gotoxy(start_x, start_y + max_lines + 1);
}

void LogUI::Render()
{
    Gotoxy(start_x, start_y);
    std::cout << "[ 전투 / 행동 로그 ]";

    for (size_t i = 0; i < messages.size(); ++i) {
        Gotoxy(start_x, start_y + 1 + i);

        // 공백을 넉넉히 줘서 이전 로그를 덮어씌움
        std::cout << messages[i] << "                          ";
    }
}

void MinimapUI::Render()
{
    Gotoxy(start_x, start_y); 
    std::cout << "+--------+";

    Gotoxy(start_x, start_y + 1);
    std::cout << "| MINIMAP|";
    Gotoxy(start_x, start_y + 2);
    std::cout << "|   @    |";

    Gotoxy(start_x, start_y + 3); 
    std::cout << "+--------+";
}

void CharacterUI::Render()
{
    // 5. 캐릭터 UI 영역 (화면 우상단 덮어쓰기)
    Gotoxy(start_x, start_y); 
    std::cout << "+------------+";

    Gotoxy(start_x, start_y + 1);
    std::cout << "| LV: 5      |";
    Gotoxy(start_x, start_y + 2);
    std::cout << "| HP: 100/100|";
    Gotoxy(start_x, start_y + 3);
    std::cout << "| MP: 50/50  |";

    Gotoxy(start_x, start_y + 4);
    std::cout << "+------------+";
}
