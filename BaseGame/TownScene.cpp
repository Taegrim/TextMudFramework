#include "TownScene.h"
#include "GameManager.h"
#include "common.h"
#include "Player.h"
#include "Status.h"
#include "UIManager.h"

void TownScene::Init()
{
    ui_list[static_cast<int>(SceneUIType::Screen)] = std::make_unique<ScreenUI>(2, 1, 15);
    ui_list[static_cast<int>(SceneUIType::CharacterInfo)] = std::make_unique<CharacterUI>(30, 1, 7);

    SetUI();
}

void TownScene::SetUI()
{
    // Character UI에 플레이어의 스탯을 출력
    std::string hp_text = "HP: " + std::to_string(player->GetStatus()[StatusType::Hp]) +
        " / " + std::to_string(player->GetStatus()[StatusType::MaxHp]);

    std::string level_text = "Lv : " + std::to_string(player->GetLevel());
    std::string exp_text = "EXP : " + std::to_string(player->GetExp());
    std::string gold_text = "GOLD : " + std::to_string(player->GetGold());

    ui_list[static_cast<int>(SceneUIType::CharacterInfo)]->AddMessage(std::string(player->GetName()) + "의 상태");
    ui_list[static_cast<int>(SceneUIType::CharacterInfo)]->AddMessage(hp_text);
    ui_list[static_cast<int>(SceneUIType::CharacterInfo)]->AddMessage(level_text);
    ui_list[static_cast<int>(SceneUIType::CharacterInfo)]->AddMessage(exp_text);
    ui_list[static_cast<int>(SceneUIType::CharacterInfo)]->AddMessage(gold_text);

    
    auto screen = GetLocalUI(SceneUIType::Screen);
    if (screen) {
        screen->Clear();
        screen->AddMessage("###########################");
        screen->AddMessage("#      평화로운 마을      #");
        screen->AddMessage("###########################");
    }


    // Global UI
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "1. 여관에서 휴식  2. 던전으로 이동");
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "원하는 행동을 선택하세요: ");
}

void TownScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(GlobalUIType::Message); // 메세지 삭제

        UIManager::GetInstance().AddMessage(GlobalUIType::Message, "1. 여관에서 휴식  2. 던전으로 이동");
        UIManager::GetInstance().AddMessage(GlobalUIType::Message, "원하는 행동을 선택하세요: ");

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[휴식] 여관에서 푹 쉬었습니다. (HP 회복)");
            player->MaxHeal();
            SetUI();
            break;

        case '2':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[이동] 어두운 던전으로 향합니다...");
            ChangeScene(SceneType::Dungeon);
            break;

        case '3':
        {
            auto info = GetLocalUI(SceneUIType::CharacterInfo);
            if (info) {
                info->ToggleVisible();
            }
            break;
        }

        default:
            UIManager::GetInstance().AddMessage(GlobalUIType::Message, "잘못된 입력입니다.");
            break;
        }
    }
}

void TownScene::Update(float delta_time)
{
}

void TownScene::Render()
{
    
}

void TownScene::Release()
{

}
