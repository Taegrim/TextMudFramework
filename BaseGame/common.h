#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <windows.h>

inline void ClearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

enum class UIType {
	Screen,
	Log,
	Minimap,
	Character,
	Message,
	COUNT
};