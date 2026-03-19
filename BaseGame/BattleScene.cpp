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
    bm = GameManager::GetInstance().GetBattleManager();

    // 1~3 마리의 몬스터와 전투
    int monster_count = RandomUtil::GetRange(1, 3);
    
    for (int i = 0; i < monster_count; ++i) {
        Monster* m = MonsterPool::GetInstance().SpawnRandomMonster();
        if (m) {
            monster_list.push_back(m);
        }
    }

    if (!bm || monster_list.empty()) {
        UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[에러] 몬스터를 생성하는데 실패했습니다...");
        PopScene();
        return;
    }
    
    bm->StartBattle(monster_list);
    current_state = BattleState::Act;

    SetUI();
}

void BattleScene::SetUI()
{
    UIManager::GetInstance().ClearMessage(GlobalUIType::Message);

    switch (current_state) {
    case BattleState::Act:
        UIManager::GetInstance().AddMessage(GlobalUIType::Message, "1. 공격한다   2. 도망친다");
        UIManager::GetInstance().AddMessage(GlobalUIType::Message, "전투 행동을 선택하세요: ");
        break;

    case BattleState::TargetEnemy:
    {
        std::string msg;
        for (int i = 0; i < monster_list.size(); ++i) {
            if (monster_list[i]->IsVisible() && !monster_list[i]->IsDead()) {
                msg += std::to_string(i + 1) + ". " + std::string(monster_list[i]->GetName()) + "  ";
            }
        }
        msg += "0. 취소";

        UIManager::GetInstance().AddMessage(GlobalUIType::Message, msg);
        UIManager::GetInstance().AddMessage(GlobalUIType::Message, "공격할 대상을 선택하세요: ");
        break;
    }

    case BattleState::TargetFriendly:
        // 아이템 사용 등 아군 선택
        break;
    }
}

void BattleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(GlobalUIType::Message);

        switch(current_state){
            // 행동 선택
        case BattleState::Act:
            switch (e.key_code) {
            case '1':
                current_state = BattleState::TargetEnemy;
                break;

            case '2':
                UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[도망] 무사히 도망쳤습니다.");
                PopScene(); // 도망 -> 이전 씬(던전)으로 복귀!
                return;

            default:
                break;
            }
            break;

            // 적 타겟 선택
        case BattleState::TargetEnemy:
        {
            if (e.key_code == '0') {
                current_state = BattleState::Act;
                break;
            }

            int idx = e.key_code - '1';

            if (idx >= 0 && idx < monster_list.size() && monster_list[idx]->IsVisible()) {
                // 플레이어 공격
                bm->PlayerAttack(idx);

                // 몬스터들의 공격
                if (!bm->IsBattleOver()) {
                    bm->MonsterAttack();
                }

                // 전투 종료 체크
                if (bm->IsBattleOver()) {
                    // 플레이어가 사망했다면 타이틀로
                    if (player->IsDead()) {
                        UIManager::GetInstance().AddMessage(GlobalUIType::Log, "게임 오버! 타이틀로 돌아갑니다...");
                        ChangeScene(SceneType::Title);
                        return;
                    }
                    else {  // 사망하지 않고 전투 종료 = 승리 -> 던전으로 복귀
                        bm->DistributeReward();
                        PopScene();
                        return;
                    }
                }
                else {  // 계속 전투중, 행동 선택지로 돌아감
                    current_state = BattleState::Act;
                }
            }

            break;
        }

            // 아군 타겟 선택
        case BattleState::TargetFriendly:
            // 아군 선택 힐, 물약 등등 처리 할것
            break;

        }

        SetUI();
    }
}

void BattleScene::Update(float delta_time)
{
}

void BattleScene::Render()
{
    int offset = 8;
    RenderSystem::GetInstance().PrintText(4, offset++, "=================================");
    RenderSystem::GetInstance().PrintText(4, offset++, "         [ 적 군 진 영 ]         ");
    

    for (int i = 0; i < monster_list.size(); ++i) {
        Monster* monster = monster_list[i];

        if (monster && monster->IsVisible() && !monster->IsDead()) {
            std::string hp_info = "[" + std::to_string(i + 1) + "] " + std::string(monster->GetName()) +
                " HP: " + std::to_string(monster->GetHp()) + " / " + std::to_string(monster->GetStatus()[StatusType::MaxHp]);

            RenderSystem::GetInstance().PrintText(4, offset++, hp_info);
        }
    }
    RenderSystem::GetInstance().PrintText(4, offset, "=============================");
}

void BattleScene::Release()
{
    for (auto& monster : monster_list) {
        if (monster) {
            monster->SetVisible(false);
        }
    }
    monster_list.clear();
}

