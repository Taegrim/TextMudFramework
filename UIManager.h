#pragma once
#include "common.h"
#include "GameUI.h"

class UIManager {
public:
    UIManager();
    ~UIManager();

    void AddMessage(UIType type, const std::string& msg);

    void Render();

private:
    std::vector<BaseUI*> ui_list;
};

