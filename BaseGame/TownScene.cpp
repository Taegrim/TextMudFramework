#include "TownScene.h"
#include "GameManager.h"
#include "common.h"
#include "Player.h"
#include "Status.h"
#include "UIManager.h"

void TownScene::Init()
{
    Player* p = GameManager::GetInstance().GetPlayer();

    // 2. Character UI에 플레이어의 스탯을 출력
    std::string hp_text = "HP: " + std::to_string(p->GetStatus()[StatusType::Hp]) +
        " / " + std::to_string(p->GetStatus()[StatusType::MaxHp]);

    UIManager::GetInstance().AddMessage(UIType::Character, std::string(p->GetName()) + "의 상태");
    UIManager::GetInstance().AddMessage(UIType::Character, hp_text);

    // 3. 마을 메인 뷰포트 및 메세지 세팅
    UIManager::GetInstance().AddMessage(UIType::Screen, "평화로운 초보자 마을입니다.");

    UIManager::GetInstance().AddMessage(UIType::Message, "1. 여관에서 휴식  2. 던전으로 이동");
    UIManager::GetInstance().AddMessage(UIType::Message, "원하는 행동을 선택하세요: ");
}

void TownScene::ProcessEvent(const Event& e)
{
    if (e.type == EventType::KeyDown) {
        UIManager::GetInstance().ClearMessage(UIType::Message); // 로그, 캐릭터창 유지

        UIManager::GetInstance().AddMessage(UIType::Message, "1. 여관에서 휴식  2. 던전으로 이동");
        UIManager::GetInstance().AddMessage(UIType::Message, "원하는 행동을 선택하세요: ");

        switch (e.key_code) {
        case '1':
            UIManager::GetInstance().AddMessage(UIType::Message, "여관에서 푹 쉬었습니다. (HP 회복)");
            // p->GetEditableStatus()->Heal(100); 같은 로직 추가 가능!
            break;
        case '2':
            UIManager::GetInstance().AddMessage(UIType::Message, "어두운 던전으로 향합니다...");
            // 던전 씬으로 ChangeScene 이벤트 푸시
            break;
        default:
            UIManager::GetInstance().AddMessage(UIType::Message, "잘못된 입력입니다.");
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
