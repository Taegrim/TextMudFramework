#pragma once
#define NOMINMAX

#include <string>
#include <array>	// 컨테이너
#include <vector>	// 컨테이너
#include <queue>	// 컨테이너
#include <algorithm>
#include <memory>		// 스마트 포인터
#include <string_view>
#include <conio.h>	// 키 입력
#include <chrono>	// 시간
#include <thread>	// sleep_for
#include <cassert>	// assert

enum class GlobalUIType {
	Log,
	Message,
	COUNT
};

enum class SceneUIType {
	Screen,
	CharacterInfo,
	Minimap,
	COUNT
};

enum class EventType {
	KeyDown,
	ChangeScene,	// 새로운 씬으로 전환
	PushScene,		// 현재 씬을 멈추고 새로운 씬 띄움
	PopScene,		// 현재 씬 끄고 아래에 있던 씬으로 복귀
	Quit
};

enum class SceneOp { Change, Push, Pop, None };

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

enum class StatusType { Hp, MaxHp, Mp, MaxMp, Atk, Def, COUNT };

enum class MonsterType {
	Slime,
	Goblin,
	None
};