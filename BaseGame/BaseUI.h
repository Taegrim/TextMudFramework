#pragma once
#include "common.h"

class BaseUI
{
public:
	BaseUI(int x, int y, int lines);
	virtual ~BaseUI() {}

	virtual void AddMessage(std::string_view msg);
	virtual void Clear();
	void SetValid(bool valid);
	bool IsValid() const;

	virtual void Render() = 0;

protected:
	int start_x;
	int start_y;
	int max_lines;
	bool is_valid;
	std::vector<std::string> messages;
};

