#include "TitleScene.h"
#include "GameManager.h"
#include "common.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
    ui_manager.AddMessage(UIType::Message, "1. 게임 시작");
    ui_manager.AddMessage(UIType::Message, "2. 게임 종료");
    ui_manager.AddMessage(UIType::Message, "원하는 메뉴의 번호를 입력하세요: ");
}

void TitleScene::Update()
{
    int input;

    if (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return;
    }

    switch (input) {
    case 1:
        ui_manager.AddMessage(UIType::Message, "게임을 시작합니다!");
        system("pause");
        break;

    case 2:
        ui_manager.AddMessage(UIType::Message, "게임을 종료합니다.");
        exit(0);
        break;

    default:
        ui_manager.AddMessage(UIType::Message, "잘못 입력하셨습니다. 다시 입력해주세요.");
        break;
    }
}

void TitleScene::Render()
{
    ui_manager.Render();
}

void TitleScene::Release()
{

}

void TitleScene::ChangeScene()
{
}
