#include "BattleScene.h"
#include "GameManager.h"
#include "MonsterPool.h"
#include "UIManager.h"
#include "RenderSystem.h"
#include "Monster.h"
#include "Player.h"
#include "BattleManager.h"

void BattleScene::Init()
{
    ui_list[static_cast<int>(SceneUIType::Screen)] = std::make_unique<ScreenUI>(2, 1, 15);

    monster = MonsterPool::GetInstance().SpawnRandomMonster();
    bm = GameManager::GetInstance().GetBattleManager();

    if (!bm || !monster) {
        UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[에러] 몬스터를 생성하는데 실패했습니다...");
        PopScene();
        return;
    }
    
    bm->StartBattle(monster);

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
            bm->PlayerAttack();

            if (!bm->IsBattleOver()) {
                bm->MonsterAttack();
            }

            if (bm->IsBattleOver()) {
                if (player->IsDead()) {

                    // 사망 시 게임오버 출력 후 타이틀로 이동
                    UIManager::GetInstance().AddMessage(GlobalUIType::Log, "게임 오버! 타이틀로 돌아갑니다.");
                    ChangeScene(SceneType::Title);
                }
                else {
                    PopScene();
                }
            }
            else {
                SetUI();
            }
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
    if (!monster) {
        return;
    }
    
    RenderSystem::GetInstance().PrintText(4, 9, "=============================");
    RenderSystem::GetInstance().PrintText(4, 10, "    " + std::string(monster->GetName()) + "와(과) 마주쳤다!   ");
    std::string hp_info = "     HP: " + std::to_string(monster->GetHp()) + " / " +
        std::to_string(monster->GetStatus()[StatusType::MaxHp]);
    RenderSystem::GetInstance().PrintText(4, 11, hp_info);
    RenderSystem::GetInstance().PrintText(4, 12, "=============================");
}

void BattleScene::Release()
{
    if (monster) {
        monster->SetVisible(false);
    }
}

