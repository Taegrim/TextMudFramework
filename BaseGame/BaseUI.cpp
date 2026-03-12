#include "BaseUI.h"

BaseUI::BaseUI(int x, int y, int lines) : start_x(x), start_y(y), max_lines(lines), isValid(true)
{
}

void BaseUI::AddMessage(const std::string& msg)
{
    messages.push_back(msg);
    if (messages.size() > max_lines) {
        messages.erase(messages.begin()); // 꽉 차면 맨 위(오래된 것) 삭제
    }
}

void BaseUI::SetValid(bool valid)
{
    isValid = valid;
}

bool BaseUI::IsValid()
{
    return isValid;
}
