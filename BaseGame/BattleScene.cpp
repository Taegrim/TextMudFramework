#include "BattleScene.h"
#include "UIManager.h"
#include "RenderSystem.h"

void BattleScene::Init()
{
    ui_list[static_cast<int>(SceneUIType::Screen)] = std::make_unique<ScreenUI>(2, 1, 15);

    SetUI();
}

void BattleScene::SetUI()
{
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "1. 공격한다   2. 도망친다");
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "전투 행동을 선택하세요: ");
}

void BattleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(GlobalUIType::Message);

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[전투] 플레이어의 공격! 슬라임을 물리쳤습니다!");
            PopScene(); // 전투 종료 -> 이전 씬(던전)으로 복귀!
            break;

        case '2':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[도망] 무사히 도망쳤습니다.");
            PopScene(); // 도망 -> 이전 씬(던전)으로 복귀!
            break;

        default:
            SetUI();
            break;
        }
    }
}

void BattleScene::Update(float delta_time)
{
}

void BattleScene::Render()
{

    RenderSystem::GetInstance().PrintText(4, 9, "=============================");
    RenderSystem::GetInstance().PrintText(4, 10, "     슬라임과 마주쳤다!    ");
    RenderSystem::GetInstance().PrintText(4, 11, "     슬라임  HP: 50 / 50    ");
    RenderSystem::GetInstance().PrintText(4, 12, "=============================");
}

void BattleScene::Release()
{
}

