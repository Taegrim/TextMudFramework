#pragma once
#include "common.h"
#include "GameUI.h"

class UIManager 
{
public:
    // 이 함수로 UIManager에 접근
    static UIManager& GetInstance() {
        static UIManager instance;
        return instance;
    }

    // 복사 생성자와 대입 연산자 삭제
    // 실수로 객체가 복사되는 것 차단
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    void AddMessage(UIType type, std::string_view msg);
    void ClearMessage(UIType type);
    void Render();
    void PrintText(int x, int y, std::string_view sv);

private:
    std::vector<std::unique_ptr<BaseUI>> ui_list;
    
    // 더블 버퍼링 관련 변수
    HANDLE screen_buffers[2];
    int current_buffer_idx;

    // 외부에서 new 못하도록 차단
    UIManager();
    ~UIManager();

    void ClearBackBuffer();
};

