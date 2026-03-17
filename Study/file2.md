# 📝 C++ 프레임워크 구현 중 발생한 문제와 핵심 개념 정리2
<br>

## 1. 콘솔 플리커링 문제 해결 과정

콘솔 창에 `Gotoxy`를 사용하여 수시로 텍스트를 출력할 때, 이동하는 위치마다 출력 커서를 띄우는 문제가 있었습니다. 이를 해결하기 위해 점진적인 개선을 거쳤습니다.

### 1단계: 커서 숨기기 및 스트림 동기화 해제
* **커서 숨기기**: `CONSOLE_CURSOR_INFO` 설정을 통해 화면에서 깜빡이는 커서를 비활성화하여 시각적인 거슬림을 줄였습니다.
* **동기화 해제**: 기존에는 `std::ios::sync_with_stdio(false)`를 호출하여 `cout`의 출력 속도를 높여서 이후 출력양이 많아져도 빠르게 처리할 수 있게 했습니다.

### 2단계: 더블 버퍼링(Double Buffering) 도입
단일 버퍼에 직접 그리는 방식은 아무리 빨라도 깜빡임을 완전히 없앨 수 없었습니다. 따라서 **두 개의 화면 버퍼**를 사용하는 방식을 도입했습니다.
* **작동 원리**: 백 버퍼(Back Buffer)에 모든 그림을 다 그린 후, 완성이 되면 전면 버퍼(Front Buffer)와 교체하여 한 번에 출력합니다.
* **변화된 점**: 
    * 백 버퍼에 먼저 그리므로 전면 버퍼의 커서를 매번 숨길 필요가 없습니다.
    * `cout` 대신 Windows API인 `WriteConsoleA`를 사용하고, `cin` 대신 비동기 키 입력인 `_getch`를 사용하므로 더 이상 스트림 동기화 해제에 의존하지 않게 되었습니다.
```
 // 버퍼 2개 생성
 screen_buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
     NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
 screen_buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
     NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

 // 두 버퍼 모두 깜빡이는 커서 숨기기
 CONSOLE_CURSOR_INFO cci;
 cci.dwSize = 1;
 cci.bVisible = FALSE;
 SetConsoleCursorInfo(screen_buffers[0], &cci);
 SetConsoleCursorInfo(screen_buffers[1], &cci);
```
```
void UIManager::Render() 
{
    // 그리기 전 Back Buffer 비우기 (이전 프레임 잔상 제거)
    ClearBackBuffer();

    // 모든 UI Back Buffer에 그리기...

    // 화면에 완성된 Back Buffer 띄우기
    SetConsoleActiveScreenBuffer(screen_buffers[current_buffer_idx]);

    // 그릴 버퍼 교체
    current_buffer_idx = (current_buffer_idx + 1) % 2;
}
```
```
void UIManager::ClearBackBuffer()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(screen_buffers[current_buffer_idx], &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Back Buffer 전체를 공백(' ')으로 채워서 싹 지워버림
    FillConsoleOutputCharacter(screen_buffers[current_buffer_idx], (TCHAR)' ',
        dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(screen_buffers[current_buffer_idx], csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten);
}
```
```
// 외부에서 호출하는 텍스트 출력 코드 (xy좌표값, 텍스트)
void UIManager::PrintText(int x, int y, std::string_view sv)
{
    DWORD dwCharsWritten;
    COORD pos = { (short)x, (short)y };

    // 현재 그리고 있는 Back Buffer의 특정 좌표로 이동
    SetConsoleCursorPosition(screen_buffers[current_buffer_idx], pos);

    // Back Buffer에 문자열 출력
    WriteConsoleA(screen_buffers[current_buffer_idx],
        sv.data(), (DWORD)sv.length(), &dwCharsWritten, NULL);
}
```

---
<br>

## 2. UI 고정 문구와 변동 문구의 분리

UI 영역에서 메뉴(고정)와 유저 선택 결과(변동)가 뒤섞여 화면이 지저분해지는 문제를 방지하기 위한 설계입니다.

* **메시지 초기화 후 재작성**: 새로운 메시지를 추가하기 전, `ClearMessage()`를 호출해 해당 구역을 깨끗이 비웁니다.
* **계층적 출력**: `Init`에서 고정 문구를 먼저 출력하고, 이후 `ProcessEvent`에서 이벤트가 발생할 때마다 고정 문구를 다시 출력한 뒤 그 아래에 선택지에 따른 결과 문구를 덧붙이는 방식을 사용합니다.

---
<br>

## 3. 씬 상태 스택 구조 최적화

인벤토리, 전체 지도, 일시정지 창처럼 기존 화면 위에 겹쳐서 나타나야 하는 기능을 위해 단순 전환(Change)이 아닌 스택(Stack) 구조를 채택했습니다.

* **[[fallthrough]]를 활용한 코드 간략화**: `Change`와 `Push`는 "기존 씬을 제거하느냐 마느냐"의 차이만 있을 뿐, 새로운 씬을 생성하고 초기화하는 로직은 동일합니다. 따라서 `switch` 문에서 `Change` 케이스 하단에 `[[fallthrough]]`를 명시하여, 기존 씬을 `Release`한 후 바로 `Push` 로직으로 넘어가게 설계하여 코드 중복을 제거했습니다.
```
// 씬 처리 과정에 Push, Pop 추가
void GameManager::ProcessScene()
{
	switch (scene_op) {
	case SceneOp::Change:
		// 기존 씬 전부 제거
		Release();
		[[fallthrough]];

	case SceneOp::Push:
		// 씬 진입 직전 UI 내용 모두 날리기
		UIManager::GetInstance().ClearAll();

		// 씬의 진입 직전 모든 UI 키기
		UIManager::GetInstance().SetAllVisible(true);

		scene_stack.push_back(CreateScene(next_scene));
		scene_stack.back()->Init();
		break;

	case SceneOp::Pop:
		if (!scene_stack.empty()) {
			scene_stack.back()->Release();
			scene_stack.pop_back();

			// Pop 시 마지막 씬이었다면 게임 종료
			if (scene_stack.empty()) {
				is_running = false;
			}
		}
		break;

	case SceneOp::None:
		// 에러
		break;
	}


	// 처리가 끝났으면 다음씬 None, 씬 동작 None
	next_scene = SceneType::None;
	scene_op = SceneOp::None;

	// 혹시 남아있다면 기존 씬의 이벤트 전부 날리기
	while (!event_queue.empty()) {
		event_queue.pop();
	}
}
```
```
// GameManager의 Run에서 최상위 씬만을 Update
while (accumulator >= delta_time) {
	if (!scene_stack.empty()) {
		scene_stack.back()->Update(delta_time);
	}
	accumulator -= delta_time;
}
```

---
<br>

## 4. Entity 시스템과 상속 구조 설계

게임 내 모든 객체를 효율적으로 관리하기 위해 추상화된 상속 구조를 구축했습니다.

* **Entity (최상위)**: 모든 객체의 공통 속성(이름, 이미지)과 `Render()` 인터페이스를 정의합니다.
* **NPC**: `Entity`를 상속받으며 전투 기능이 없는 순수 상호작용 개체입니다.
* **BattleEntity (전투 개체)**: 전투 기능이 필요한 `Player`와 `Monster`의 부모 클래스입니다. `Status` 클래스를 멤버 변수로 부착하여 체력, 공격력 등의 데이터를 독립적으로 관리합니다.
