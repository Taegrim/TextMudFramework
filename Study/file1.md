# 📝 C++ 프레임워크 구현 중 발생한 문제와 핵심 개념 정리1
<br>

## 1. GameManager, UIManager에 싱글톤 패턴 적용 (마이어스 싱글톤)

기존 포인터 방식(`new/delete`)의 싱글톤 패턴이 가진 한계를 극복하기 위해 **마이어스 싱글톤(Meyers' Singleton)** 방식을 도입했습니다.

### 기존 포인터 방식의 문제점
1. **메모리 관리의 어려움:** 전역에서 쓰이는 클래스이므로 `delete` 시점을 명확히 잡기 어려워 메모리 누수의 위험이 있습니다.
2. **멀티스레드 취약성:** 멀티스레드 환경에서 인스턴스를 동시에 요청할 경우 동기화 문제가 발생할 수 있습니다. 
> **해결:** C++11 이후부터는 **정적 지역 변수(Static local variable) 초기화가 멀티스레드 환경에서 안전함을 언어 차원에서 보장**하므로 이를 해결할 수 있습니다.

### 💡 마이어스 싱글톤의 핵심: `GetInstance()` 내부에서의 선언
정적 멤버 변수는 같은 `.cpp` 파일의 전역 공간에서 정의를 해야 하는데, C++은 **다른 `.cpp` 파일에 있는 정적 변수들의 초기화 순서를 보장하지 않습니다.**

* **발생 가능한 오류 시나리오:** 정적 변수들은 `main()` 시작 전에 메모리에 올라가고 초기화됩니다. 만약 `GameManager`의 생성자에서 `UIManager::GetInstance()`를 호출하는데, 프로그램이 `GameManager`를 먼저 초기화해버리면 아직 메모리에 없는 `UIManager`를 참조하게 되어 치명적인 오류가 발생합니다.
* **마이어스 싱글톤의 이점 :**
  정적 변수를 `GetInstance()` 함수 내부의 지역 변수로 선언하면, 프로그램 시작 시점이 아니라 **해당 함수가 최초로 호출될 때 초기화**되므로 초기화 순서 꼬임 문제가 완벽하게 해결됩니다.

```cpp
class UIManager 
{
public:
    // 이 함수로 UIManager에 접근
    static UIManager& GetInstance() {
        static UIManager instance;
        return instance;
    }

    // 복사 생성자와 대입 연산자 삭제
    // 실수로 객체가 복사되는 것 차단
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    // 내부 처리 함수

private:
    // 멤버 변수

    // 외부에서 new 못하도록 차단
    UIManager();
    ~UIManager();
};
```

---
<br>

## 2. 싱글톤 패턴 적용 기준

싱글톤 패턴은 남용하면 객체 지향 원칙에 위배되므로, 명확한 기준을 세워 적용해야 합니다.

* **✅ 싱글톤을 적용하기 좋은 경우 (Core Systems)**
  * 프로그램 전체를 통틀어 물리적/논리적으로 **하나만 존재**해야 하는 경우
  * 예: `GameManager`, `SoundManager`, `FileSystem` 등
* **❌ 싱글톤 적용을 피해야 하는 경우 (Game Logic)**
  * 특정 게임 씬이나 모드, 객체에 종속적인 경우
  * 예: `BattleManager` (전투 씬에서만 필요하며 씬 종료 시 삭제되어야 함)
  * 예: `MonsterManager`, `InventoryManager` (플레이어 객체나 특정 상태에 종속되는 것이 바람직함)

---
<br>

## 3. 고정 스텝 게임 루프

다음과 같은 원칙으로 게임 루프를 설계했습니다.

1. **입력/이벤트 상시 처리:** 유저의 키 씹힘을 방지하기 위해 이벤트 처리는 루프가 돌 때마다 쉬지 않고 감지하고 처리합니다.
2. **고정 스텝 업데이트:** 로직(로테이션, 이동, 쿨타임 등)은 기기 성능에 상관없이 **1/60초(약 16.66ms)** 마다 일정하게 수행되도록 합니다.
3. **조건부 렌더링:** `Update`가 수행되어 **상태에 변화가 생겼을 때만 렌더링**을 수행합니다. 변화가 없다면 이전 프레임 화면을 유지해도 되기 때문입니다.

```cpp
void GameManager::Run()
{
	// 60fps -> 1프레임당 약16.66ms
	constexpr float delta_time = 1.f / 60.f;

	auto last = std::chrono::steady_clock::now();
	float accumulator = 0.f;	// 경과한 시간 누적

	while (is_running) {
		auto current = std::chrono::steady_clock::now();
		std::chrono::duration<float> elapsed = current - last;
		last = current;

		// 이번 루프에 걸린 시간
		accumulator += elapsed.count();

		// KeyDown 이벤트 감지
		ProcessInput();

		// 이벤트 처리는 계속 확인
		while (!event_queue.empty()) {
			// 이벤트 처리...
		}

		// 16.66ms가 지났다면 update, render
		if (accumulator >= delta_time) {

			// 만약 렉으로 처리가 늦어 시간이 밀렸다면 반복해서 처리
			while (accumulator >= delta_time) {
				if (scene) {
					scene->Update(delta_time);
				}
				accumulator -= delta_time;
			}

			// 씬 교체
			if (next_scene != SceneType::None) {
				ChangeScene();
			}
            
			// 로직 업데이트가 끝났다면 최신 상태 그리기
			UIManager::GetInstance().Render();
		}

		// 짧게 휴식
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
```

---
<br>

## 4. Scene 상태 패턴 및 지연된 씬 전환

씬(Scene) 관리를 위해 상태 패턴(State Pattern)을 사용하며, 씬 전환 시 발생할 수 있는 메모리 참조 버그를 예방하고자 했습니다.

### 씬 즉시 전환의 위험성
씬 내부의 `Update()` 실행 도중 `ChangeScene()`을 호출하여 즉시 현재 씬을 `Release`(메모리 해제)해 버리면, 함수 종료 후 돌아갈 메모리 주소가 사라져 프로그램이 강제 종료됩니다.
> **해결:** `ChangeScene()` 호출 시 즉시 씬을 바꾸지 않고, **다음 씬(Next Scene)을 예약만 해둔 뒤 프레임의 맨 끝에서 교체**합니다.

### 씬 전환을 이벤트(Event)로 처리하기
씬 전환 역시 `Event` 구조체를 활용해 이벤트 큐에 넣어 처리하도록 결합도를 낮췄습니다.
* **메모리 최적화:** `union` 문법을 사용하여 `Event` 구조체 내에서 키보드 입력 값(`key_code`)과 씬 전환 값(`next_scene`)이 같은 메모리 공간을 공유하도록 설계했습니다.

### 논리적인 씬 전환 타이밍
이벤트 큐에서 씬 전환 이벤트를 발견했다고 해서 그 즉시 씬을 교체해서는 안 됩니다.
* **이유:** 기존 파이프라인(`이벤트 처리 -> Update -> Render`) 도중 이벤트 단계에서 씬을 갈아끼우면, 새로 태어난 씬이 초기화되자마자 불완전한 델타 타임(Delta Time)으로 `Update`를 맞게 되는 논리적 오류가 발생할 수 있습니다.
* **결론:** 따라서 씬 전환 이벤트는 예약 처리만 해두고, **루프의 모든 로직(`Event`, `Update`)이 완전히 끝난 후 가장 안전한 타이밍에 씬 전환을 수행**하는 것이 바람직합니다.

```cpp
while (!event_queue.empty()) {
	Event ev = event_queue.front();
	event_queue.pop();

    이벤트 처리 단계에선 다음 씬 예약
	switch (ev.type) {
    // 다른 이벤트 처리...

	case EventType::ChangeScene:
		next_scene = ev.next_scene;
		break;
	}
}
```
```cpp
void GameManager::ChangeScene()
{
	// 기존 씬 제거
	if (scene) {
		scene->Release();
		scene.reset();
	}

	// 새로운 씬 생성
	switch (next_scene) {
	// 씬 생성...
	}

	// 씬 초기화
	if (scene) {
		scene->Init();
	}

	// 씬 생성했으니 다음 씬 None으로 바꿔주기
	next_scene = SceneType::None;

	// 혹시 남아있다면 기존 씬의 이벤트 전부 날리기
	while (!event_queue.empty()) {
		event_queue.pop();
	}
}
```
```cpp
void GameManager::Run()
{
	// 시간 계산...

	while (is_running) {
		// 시간 계산...

		// KeyDown 이벤트 감지

		// 이벤트 처리...

		// 16.66ms가 지났다면 update, render
		if (accumulator >= delta_time) {
            // Update...

			// 실제 씬 교체
			if (next_scene != SceneType::None) {
				ChangeScene();
			}

			// Render...
		}
	}
}
```