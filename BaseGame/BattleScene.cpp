#include "BattleScene.h"
#include "UIManager.h"

void BattleScene::Init()
{
    UIManager::GetInstance().AddMessage(UIType::Screen, "슬라임과 마주쳤다!");
    UIManager::GetInstance().AddMessage(UIType::Screen, "슬라임  HP: 50 / 50");

    UIManager::GetInstance().AddMessage(UIType::Message, "1. 공격한다   2. 도망친다");
    UIManager::GetInstance().AddMessage(UIType::Message, "전투 행동을 선택하세요: ");
}

void BattleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(UIType::Message);

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Log, "[전투] 플레이어의 공격! 슬라임을 물리쳤습니다!");
            PopScene(); // 전투 종료 -> 이전 씬(던전)으로 복귀!
            break;

        case '2':
            UIManager::GetInstance().AddMessage(UIType::Log, "[도망] 무사히 도망쳤습니다.");
            PopScene(); // 도망 -> 이전 씬(던전)으로 복귀!
            break;

        default:
            UIManager::GetInstance().AddMessage(UIType::Message, "1. 공격한다 (승리)   2. 도망친다");
            UIManager::GetInstance().AddMessage(UIType::Message, "잘못된 입력입니다.");
            break;
        }
    }
}

void BattleScene::Update(float delta_time)
{
}

void BattleScene::Render()
{
}

void BattleScene::Release()
{
}
