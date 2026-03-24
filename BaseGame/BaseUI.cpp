#include "BaseUI.h"

BaseUI::BaseUI(int x, int y, unsigned int lines) : start_x(x), start_y(y), max_lines(lines),
    is_visible(true)
{
    max_messages = std::max(static_cast<unsigned int>(1), static_cast<unsigned int>(lines - 3));
}

void BaseUI::AddMessage(std::string_view msg)
{
    messages.emplace_back(msg);
    if (static_cast<unsigned int>(messages.size()) > max_messages) {
        messages.pop_front(); // 꽉 차면 맨 위(오래된 것) 삭제
    }
}

void BaseUI::Clear()
{
    messages.clear();
}

void BaseUI::SetVisible(bool valid)
{
    is_visible = valid;
}

void BaseUI::ToggleVisible()
{
    is_visible = !is_visible;
}

bool BaseUI::IsVisible() const
{
    return is_visible;
}
