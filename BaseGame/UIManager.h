#pragma once
#include "common.h"
#include "GameUI.h"
#include <windows.h>

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

    void AddMessage(GlobalUIType type, std::string_view msg);
    void ClearMessage(GlobalUIType type);
    void ClearAll(const std::vector<GlobalUIType>& ignore_list = {});
    void Render();  // 로그, 선택지 그리기
    void SetVisible(GlobalUIType type, bool value);
    void SetAllVisible(bool value = true);

private:
    std::vector<std::unique_ptr<BaseUI>> ui_list;

    // 외부에서 new 못하도록 차단
    UIManager();
    ~UIManager();
};

