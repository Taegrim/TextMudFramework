#include "DungeonScene.h"
#include "UIManager.h"
#include "RenderSystem.h"

void DungeonScene::Init()
{
    ui_list[static_cast<size_t>(SceneUIType::Screen)] = std::make_unique<ScreenUI>(2, 1, 15);
    ui_list[static_cast<size_t>(SceneUIType::Minimap)] = std::make_unique<MinimapUI>(2, 2, 5);

    SetUI();
    SetMenu();
}

void DungeonScene::SetUI()
{
    auto minimap = GetLocalUI(SceneUIType::Minimap);
    if (minimap) {
        minimap->Clear();
        minimap->AddMessage("#######");
        minimap->AddMessage("#  O  #");
        minimap->AddMessage("#######");
    }

    auto screen = GetLocalUI(SceneUIType::Screen);
    if (screen) {
        screen->Clear();
        screen->AddMessage("");
        screen->AddMessage("");
        screen->AddMessage("");
        screen->AddMessage("");
        screen->AddMessage("");
        screen->AddMessage("=============================");
        screen->AddMessage("[ 음산한 기운이 감도는 던전 ]");
        screen->AddMessage("=============================");
    }
}

void DungeonScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(GlobalUIType::Menu);
    UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "1. 내부 탐색 (몬스터 조우)   2. 마을로 귀환한다  3. 미니맵 on/off");
    UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "어떤 행동을 하시겠습니까?: ");
}

void DungeonScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        SetMenu();

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[조우] 몬스터와 조우했습니다!");
            PushScene(SceneType::Battle);
            break;

        case '2':
            UIManager::GetInstance().AddMessage(GlobalUIType::Log, "[이동] 마을로 귀환합니다...");
            ChangeScene(SceneType::Town);
            break;

        case '3':
        {   
            auto minimap = GetLocalUI(SceneUIType::Minimap);
            if (minimap) {
                minimap->ToggleVisible();
            }
            break;
        }

        case 'i':
        case 'I':
            PushScene(SceneType::Inventory);
            break;

        default:
            UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "잘못된 입력입니다.");
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
