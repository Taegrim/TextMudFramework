#include "GameManager.h"
#include "TitleScene.h"

GameManager::GameManager() : scene(nullptr), next_scene(SceneType::None), is_running(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	scene = std::make_unique<TitleScene>();
	scene->Init();
}

// 고정 스텝 방식
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
			Event ev = event_queue.front();
			event_queue.pop();

			switch (ev.type) {
			case EventType::KeyDown:
				if (scene) {
					scene->ProcessEvent(ev);
				}
				break;

			case EventType::ChangeScene:
				next_scene = ev.next_scene;
				break;

			case EventType::Quit:
				is_running = false;
				break;
			}
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

void GameManager::Release()
{
	if (scene) {
		scene->Release();
	}
}

void GameManager::PushEvent(const Event& ev)
{
	event_queue.push(ev);
}



// ------ private 함수 -----
void GameManager::ProcessInput()
{
	if (_kbhit()) {
		int key = _getch();

		Event ev;
		ev.type = EventType::KeyDown;
		ev.key_code = key;
		event_queue.push(ev);
	}
}

void GameManager::ChangeScene()
{
	// 기존 씬 제거
	if (scene) {
		scene->Release();
		scene.reset();
	}

	// 새로운 씬 생성
	switch (next_scene) {
	case SceneType::Title:
		scene = std::make_unique<TitleScene>();
		break;
	case SceneType::Town:
		//scene = std::make_unique<TownScene>();
		break;
	case SceneType::Dungeon:
		//scene = std::make_unique<DungeonScene>();
		break;
	case SceneType::Battle:
		//scene = std::make_unique<BattleScene>();
		break;
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
