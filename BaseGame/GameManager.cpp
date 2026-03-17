#include "GameManager.h"
#include "TitleScene.h"
#include "TownScene.h"
#include "Player.h"
#include "UIManager.h"

GameManager::GameManager() : scene_stack(), scene_op(SceneOp::None),
	next_scene(SceneType::None), is_running(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	UIManager::GetInstance().SetAllVisible(true);

	// 플레이어 생성
	player = std::make_unique<Player>("용사", "@", Status(100, 100, 10, 10, 50, 30));

	// 초기 씬
	scene_stack.push_back(CreateScene(SceneType::Title));
	scene_stack.back()->Init();
}

// 고정 스텝 방식 게임 루프
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
				if (!scene_stack.empty()) {
					scene_stack.back()->ProcessEvent(ev);
				}
				break;

			case EventType::ChangeScene:
				scene_op = SceneOp::Change;
				next_scene = ev.next_scene;
				break;

			case EventType::PushScene:
				scene_op = SceneOp::Push;
				next_scene = ev.next_scene;
				break;

			case EventType::PopScene:
				scene_op = SceneOp::Pop;
				break;

			case EventType::Quit:
				is_running = false;
				break;
			}

			// 씬 전환 예약되었으면 이후에 다른 event가 있어도 무시
			if (scene_op != SceneOp::None) {
				break;
			}
		}

		// 16.66ms가 지났다면 update, render
		if (accumulator >= delta_time) {

			// 만약 렉으로 처리가 늦어 시간이 밀렸다면 반복해서 처리
			while (accumulator >= delta_time) {
				if (!scene_stack.empty()) {
					scene_stack.back()->Update(delta_time);
				}
				accumulator -= delta_time;
			}

			// 씬 Change, Push, Pop 처리
			if (scene_op != SceneOp::None) {
				ProcessScene();
			}

			// 로직 업데이트가 끝났다면 최신 상태 그리기
			UIManager::GetInstance().Render();
		}

		// 짧게 휴식
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

// 할당한 씬 전부 제거
void GameManager::Release()
{
	while (!scene_stack.empty()) {
		scene_stack.back()->Release();
		scene_stack.pop_back();
	}
}

void GameManager::PushEvent(const Event& ev)
{
	event_queue.push(ev);
}

Player* GameManager::GetPlayer() const
{
	return player.get();
}



// ------ private 함수 -----
void GameManager::ProcessInput()
{
	if (_kbhit()) {
		int key = _getch();

		Event ev{};
		ev.type = EventType::KeyDown;
		ev.key_code = key;
		event_queue.push(ev);
	}
}

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

// 새로운 씬 생성 함수
std::unique_ptr<BaseScene> GameManager::CreateScene(SceneType type)
{
	switch (type) {
	case SceneType::Title:
		return std::make_unique<TitleScene>();
		
	case SceneType::Town:
		return std::make_unique<TownScene>();
		
	case SceneType::Dungeon:
		//return std::make_unique<DungeonScene>();
		break;
	case SceneType::Battle:
		//return std::make_unique<BattleScene>();
		break;
	}
	return nullptr;
}
