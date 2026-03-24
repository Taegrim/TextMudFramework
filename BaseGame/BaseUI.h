#pragma once
#include "common.h"

class BaseUI
{
public:
	BaseUI(int x, int y, unsigned int lines);
	virtual ~BaseUI() = default;

	void AddMessage(std::string_view msg);
	void Clear();

	void SetVisible(bool valid);
	void ToggleVisible();
	bool IsVisible() const;

	virtual void Render() = 0;

protected:
	int start_x;
	int start_y;
	unsigned int max_lines;
	unsigned int max_messages;
	bool is_visible;
	std::deque<std::string> messages;
};

