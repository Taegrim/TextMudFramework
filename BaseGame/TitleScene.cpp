#include "TitleScene.h"
#include "GameManager.h"
#include "common.h"
#include "UIManager.h"

void TitleScene::Init()
{
    UIManager::GetInstance().SetVisible(UIType::Log, false);
    UIManager::GetInstance().SetVisible(UIType::Minimap, false);
    UIManager::GetInstance().SetVisible(UIType::Character, false);

    UIManager::GetInstance().AddMessage(UIType::Message, "1. 게임 시작   2. 게임 종료");
    UIManager::GetInstance().AddMessage(UIType::Message, "원하는 메뉴의 번호를 입력하세요: ");
}

void TitleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {

        // 메세지 창 전부 비우기
        UIManager::GetInstance().ClearMessage(UIType::Message);

        // 고정 문구 적기
        UIManager::GetInstance().AddMessage(UIType::Message, "1. 게임 시작   2. 게임 종료");
        UIManager::GetInstance().AddMessage(UIType::Message, "원하는 메뉴의 번호를 입력하세요: ");

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Message, "게임을 시작합니다!");
            ChangeScene(SceneType::Town);
            break;

        case '2':
        {
            UIManager::GetInstance().AddMessage(UIType::Message, "게임을 종료합니다.");

            Event ev{};
            ev.type = EventType::Quit;
            GameManager::GetInstance().PushEvent(ev);
            break;
        }

        default:
            UIManager::GetInstance().AddMessage(UIType::Message, "잘못 입력하셨습니다. 다시 입력해주세요.");
            break;
        }
    }
}

void TitleScene::Update(float delta_time)
{
    // 애니메이션, 타이머 등
}

void TitleScene::Render()
{
}

void TitleScene::Release()
{
}

