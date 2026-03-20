# 📝 C++ 프레임워크 구현 중 발생한 문제와 핵심 개념 정리4
<br>

## 1. 아이템 시스템 및 상속 구조 설계

다양한 아이템을 체계적으로 관리하기 위해 최상위 클래스 `Item`을 필두로 한 상속구조를 구축하고, 장비형 아이템의 세부 분류를 정의했습니다.

* **상속 구조**: `Item (Base)` → `Equipment`, `Consumable`, `JunkItem`
* **장비 세분화**: `Equipment` 내부에 `EquipmentSlot`을 두어 무기, 갑옷, 악세서리(1, 2)를 구분합니다.
* **인터페이스 최적화**: `Use()`를 가상 함수로 선언하여 외부(인벤토리 등)에서 아이템 종류를 일일이 체크하지 않고 `item->Use(player)`만으로 장비 장착과 소모품 사용 로직을 모두 처리할 수 있게 설계했습니다.

```cpp
// 임시로 장비를 장착하는 코드
Equipment* weapon = player->GetEquippedItem(EquipmentSlot::Weapon);

if (weapon) {
    weapon->Use(player);
}
else {
    // 인벤토리 비어있다면 생성
    if (player->GetInventory().empty()) {
        auto test_sword = std::make_unique<Equipment>("녹슨검", "테스트용", 0, EquipmentSlot::Weapon);

        test_sword->SetBonusStat({
            {StatusType::Atk, 6},
            {StatusType::MaxHp, 50}
            });

        player->AddItem(std::move(test_sword));
    }

    // item->Use() 아이템 종류에 상관없이 처리 가능
    Item* item = player->GetInventory()[0].get();
    item->Use(player);
}
```
---
<br>

## 2. 장비 보너스를 포함한 스테이터스 시스템 확장

장비 장착에 따른 능력치 변화를 효율적으로 처리하기 위해 기본 능력치(Base)와 추가 능력치(Bonus)를 분리하고 접근 로직을 수정했습니다.

* **보너스 데이터 구조**: 장비 클래스에 `std::vector<std::pair<StatusType, int>>`를 추가하여 하나의 장비가 여러 종류의 능력치를 가변적으로 올려줄 수 있도록 설계했습니다.
* **`operator[]` 리팩토링**: 외부에서 스탯 값을 참조할 때 `GetTotal()`을 거치도록 하여 **기본값 + 보너스값**이 합산된 최종 수치만을 반환합니다.
* **논리적 예외 처리**: 현재 체력은 장비 보너스에 의해 증가하지 않으므로 해당 구조에서 문제가 없습니다.

```cpp
// Status 클래스 내 연산자 오버로딩 예시
int operator[](StatusType type) const {
	return GetTotal(type);
}

int Status::GetTotal(StatusType type) const
{
	assert(static_cast<int>(type) >= 0 &&
		static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

	return status[static_cast<int>(type)] + bonus_status[static_cast<int>(type)];
}
```
```cpp
// 기존에 base stat 만 있을 때 status[StatusType::Hp] 로 스탯을 변경하기 위한 연산자 오버로딩
// 지금은 삭제함
const int& operator[](StatusType type) const {
		assert(static_cast<int>(type) >= 0 &&
			static_cast<int>(type) < static_cast<int>(StatusType::COUNT));

		return status[static_cast<int>(type)];
	}
```

---
<br>

## 3. UI 출력 로직 분리 및 최적화

전역 UI와 특정 씬의 로컬 UI가 중복 출력되는 문제를 해결하기 위해 호출 주체를 명확히 분리했습니다.

* **`SetUI`**: 각 씬(`BaseScene`)이 소유한 로컬 UI 요소들만 세팅합니다.
* **`SetMenu` (기존 Message)**: 유저에게 선택지를 제공하는 전역 UI로, `UIManager`를 통해 제어하며 필요한 시점(Init 혹은 상태 변화)에만 명시적으로 호출합니다.

```cpp
// info, screen 등 씬마다 개별로 가질 ui들을 세팅
void BattleScene::SetUI()
{
    // 플레이어 체력 표시
    auto info = GetLocalUI(SceneUIType::CharacterInfo);
    if (info) {
        info->Clear();
        // 캐릭터 info 출력
    }

    auto screen = GetLocalUI(SceneUIType::Screen);
    if (screen) {
        screen->Clear();

        screen->AddMessage("=================================");
        screen->AddMessage("         [ 적 군 진 영 ]         ");
        // 적군 상태 출력
        screen->AddMessage("=================================");
    }
}
```
```cpp
// 플레이어의 다음 행동을 제시하는 메뉴판 세팅
void BattleScene::SetMenu()
{
    UIManager::GetInstance().ClearMessage(GlobalUIType::Menu);

    switch (current_state) {
    case BattleState::Act:
        UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "1. 공격한다   2. 도망친다");
        UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "전투 행동을 선택하세요: ");
        break;

    case BattleState::TargetEnemy:
    {
        std::string msg;
        // 적 내용
        UIManager::GetInstance().AddMessage(GlobalUIType::Menu, "공격할 대상을 선택하세요: ");
        break;
    }

    case BattleState::TargetFriendly:
        // 아이템 사용 등 아군 선택
        break;
    }
}
```
