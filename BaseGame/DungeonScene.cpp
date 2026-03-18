#include "DungeonScene.h"
#include "UIManager.h"

void DungeonScene::Init()
{
    OnEnter();
}

void DungeonScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(UIType::Message);

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Log, "[조우] 몬스터와 조우했습니다!");
            PushScene(SceneType::Battle);
            break;

        case '2':
            UIManager::GetInstance().AddMessage(UIType::Log, "[이동] 마을로 귀환합니다...");
            ChangeScene(SceneType::Town);
            break;

        default:
            OnEnter(); // 화면 다시 출력
            UIManager::GetInstance().AddMessage(UIType::Message, "잘못된 입력입니다.");
            break;
        }
    }
}

void DungeonScene::Update(float delta_time)
{
}

void DungeonScene::Render()
{
}

void DungeonScene::Release()
{
}

void DungeonScene::OnEnter()
{
    UIManager::GetInstance().ClearMessage(UIType::Screen);
    UIManager::GetInstance().ClearMessage(UIType::Message);

    UIManager::GetInstance().AddMessage(UIType::Screen, "음산한 기운이 감도는 던전입니다.");

    UIManager::GetInstance().AddMessage(UIType::Message, "1. 내부 탐색 (몬스터 조우)   2. 마을로 도망친다");
    UIManager::GetInstance().AddMessage(UIType::Message, "어떤 행동을 하시겠습니까?: ");
}
