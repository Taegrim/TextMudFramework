#pragma once
#include "common.h"

class BaseUI
{
public:
	BaseUI(int x, int y, int lines);
	virtual ~BaseUI() {}

	virtual void AddMessage(const std::string& msg);
	void SetValid(bool valid);
	bool IsValid();

	virtual void Render() = 0;

protected:
	int start_x;
	int start_y;
	int max_lines;
	bool isValid;
	std::vector<std::string> messages;

	void Gotoxy(int x, int y) {
		COORD pos = { (short)x, (short)y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
};

