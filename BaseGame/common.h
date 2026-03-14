#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>		// 스마트 포인터
#include <windows.h>
#include <string_view>
#include <queue>
#include <conio.h>	// 키 입력
#include <chrono>	// 시간
#include <thread>	// sleep_for

enum class UIType {
	Screen,
	Log,
	Minimap,
	Character,
	Message,
	None
};

enum class EventType {
	KeyDown,
	ChangeScene,
	Quit
};

enum class SceneType {
	Title,
	Town,
	Dungeon,
	Battle,
	None
};

struct Event {
	EventType type;

	// 같은 메모리 공간을 겹쳐서 사용
	// 이후에 다른 이벤트가 추가되더라도 추가되는 메모리가 없을것
	union {
		int key_code;
		SceneType next_scene;
	};
};
