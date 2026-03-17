#include "BaseUI.h"

BaseUI::BaseUI(int x, int y, int lines) : start_x(x), start_y(y), max_lines(lines),
    is_valid(true)
{
    max_messages = std::max(1, lines - 3);
}

void BaseUI::AddMessage(std::string_view msg)
{
    messages.emplace_back(msg);
    if (messages.size() > max_messages) {
        messages.erase(messages.begin()); // 꽉 차면 맨 위(오래된 것) 삭제
    }
}

void BaseUI::Clear()
{
    messages.clear();
}

void BaseUI::SetValid(bool valid)
{
    is_valid = valid;
}

bool BaseUI::IsValid() const
{
    return is_valid;
}
