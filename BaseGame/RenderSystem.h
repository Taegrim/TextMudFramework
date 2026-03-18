#pragma once
#include "common.h"
#include <windows.h>

class RenderSystem
{
public:
	static RenderSystem& GetInstance() {
		static RenderSystem instance;
		return instance;
	}

	// 복사 생성자와 대입 연산자 삭제
	// 실수로 객체가 복사되는 것 차단
	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	void ClearBuffer(); // 버퍼 지우기
	void Draw();   // 출력 & 버퍼교체
	void PrintText(int x, int y, std::string_view sv);

private:
	// 더블 버퍼링 관련 변수
	HANDLE screen_buffers[2];
	int current_buffer_idx = 0;

	// 외부에서 new 못하도록 차단
	RenderSystem();
	~RenderSystem();
};

