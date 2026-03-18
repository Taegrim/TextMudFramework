#include "TitleScene.h"
#include "GameManager.h"
#include "common.h"
#include "UIManager.h"

void TitleScene::Init()
{
    UIManager::GetInstance().SetVisible(GlobalUIType::Log, false);

    SetUI();
}

void TitleScene::SetUI()
{
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "1. 게임 시작   2. 게임 종료");
    UIManager::GetInstance().AddMessage(GlobalUIType::Message, "원하는 메뉴의 번호를 입력하세요: ");
}

void TitleScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {

        // 메세지 창 전부 비우기
        UIManager::GetInstance().ClearMessage(GlobalUIType::Message);

        // 고정 문구 적기
        SetUI();

        switch (e.key_code) {
        case '1':
            ChangeScene(SceneType::Town);
            break;

        case '2':
        {
            Event ev{};
            ev.type = EventType::Quit;
            GameManager::GetInstance().PushEvent(ev);
            break;
        }

        default:
            UIManager::GetInstance().AddMessage(GlobalUIType::Message, "잘못 입력하셨습니다. 다시 입력해주세요.");
            break;
        }
    }
}

void TitleScene::Update(float delta_time)
{
}

void TitleScene::Render()
{
}

void TitleScene::Release()
{
}

