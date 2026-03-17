#pragma once
#include "BaseScene.h"
#include "UIManager.h"

class GameManager
{
public:
    static GameManager& GetInstance() {
        static GameManager instance;
        return instance;
    }

    // 복사 생성자와 대입 연산자 삭제
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    void Init();
    void Run();
    void Release();
    void PushEvent(const Event& ev);

private:
	std::vector<std::unique_ptr<BaseScene>> scene_stack;
    SceneOp scene_op;
    SceneType next_scene;
	bool is_running;
    std::queue<Event> event_queue;


    GameManager();
    ~GameManager();

    void ProcessInput();
    void ProcessScene();
    std::unique_ptr<BaseScene> CreateScene(SceneType type);
};

