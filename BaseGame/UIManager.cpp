#include "UIManager.h"

UIManager::UIManager() : current_buffer_idx(0)
{
    // 버퍼 2개 생성
    screen_buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    screen_buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
        NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 두 버퍼 모두 깜빡이는 커서 숨기기
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(screen_buffers[0], &cci);
    SetConsoleCursorInfo(screen_buffers[1], &cci);

    // UI : x, y, max_line
    // 0: Screen (x:2, y:2, 15줄)
    ui_list.push_back(std::make_unique<ScreenUI>(2, 2, 15));

    // 1: Log (x:62, y:1, 15줄)
    ui_list.push_back(std::make_unique<LogUI>(62, 1, 15));

    // 2: Minimap (x:2, y:2, 5줄) -> 덮어쓰기
    ui_list.push_back(std::make_unique<MinimapUI>(2, 2, 5));

    // 3: Character (x:30, y:2, 5줄) -> 덮어쓰기
    ui_list.push_back(std::make_unique<CharacterUI>(30, 2, 5));

    // 4: Message (x:0, y:21, 4줄)
    ui_list.push_back(std::make_unique<MessageUI>(0, 21, 4));
}

UIManager::~UIManager()
{
    CloseHandle(screen_buffers[0]);
    CloseHandle(screen_buffers[1]);
}

void UIManager::AddMessage(UIType type, std::string_view msg)
{
    int idx = static_cast<int>(type);

    if (idx >= 0 && idx < static_cast<int>(UIType::None)) {
        ui_list[idx]->AddMessage(msg);
    }
}

void UIManager::ClearMessage(UIType type)
{
    int idx = static_cast<int>(type);

    if (idx >= 0 && idx < static_cast<int>(UIType::None)) {
        ui_list[idx]->Clear();
    }
}

void UIManager::ClearAll(const std::vector<UIType>& ignore_list)
{
    for (int i = 0; i < static_cast<int>(UIType::None); ++i) {
        UIType current_type = static_cast<UIType>(i);

        auto it = std::find(ignore_list.begin(), ignore_list.end(), current_type);
        if (it != ignore_list.end()) {
            continue;
        }

        ui_list[i]->Clear();
    }
}

void UIManager::Render() 
{
    // 그리기 전 Back Buffer 비우기 (이전 프레임 잔상 제거)
    ClearBackBuffer();

    // 모든 UI Back Buffer에 그리기
    for (const auto& ui : ui_list) {
        if (ui->IsValid()) {
            ui->Render();
        }
    }

    // 화면에 완성된 Back Buffer 띄우기
    SetConsoleActiveScreenBuffer(screen_buffers[current_buffer_idx]);

    // 그릴 버퍼 교체
    current_buffer_idx = (current_buffer_idx + 1) % 2;
}

void UIManager::PrintText(int x, int y, std::string_view sv)
{
    DWORD dwCharsWritten;
    COORD pos = { (short)x, (short)y };

    // 현재 그리고 있는 Back Buffer의 특정 좌표로 이동
    SetConsoleCursorPosition(screen_buffers[current_buffer_idx], pos);

    // Back Buffer에 문자열 출력
    WriteConsoleA(screen_buffers[current_buffer_idx],
        sv.data(), (DWORD)sv.length(), &dwCharsWritten, NULL);
}

void UIManager::SetVisible(UIType type, bool value)
{
    int idx = static_cast<int>(type);
    if (idx >= 0 && idx < static_cast<int>(UIType::None)) {
        ui_list[idx]->SetValid(value);
    }
}

void UIManager::SetAllVisible(bool value)
{
    for (auto& ui : ui_list) {
        ui->SetValid(value);
    }
}



// private 함수
void UIManager::ClearBackBuffer()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Back Buffer 전체를 공백(' ')으로 채워서 싹 지워버림
    FillConsoleOutputCharacter(screen_buffers[current_buffer_idx], (TCHAR)' ',
        dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(screen_buffers[current_buffer_idx], csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten);
}