# 🛡️ C++ Text MUD Game Framework

본 프로젝트는 C++17 이상을 기반으로 작성된 **콘솔 텍스트 기반 MUD 게임 전용 프레임워크**입니다.

<br>

## 🗂️ 클래스 구조 (Architecture)
<img width="1769" height="997" alt="UML" src="https://github.com/user-attachments/assets/b7555512-4044-469a-b0ec-ca5d795beeb3" />

* **`GameManager`**: 메인 루프 실행, 이벤트 큐 관리 및 씬 전환을 담당하는 프레임워크의 핵심입니다.
* **`UIManager`**: 등록된 전체 UI 컴포넌트들을 관리하고 화면에 일괄 렌더링합니다.
* **`BaseScene` / `TitleScene`**: 게임의 각 상태(화면)를 정의하는 추상 클래스 및 그 구현체입니다. 
* **`BaseUI` / `ScreenUI`, `LogUI`, `MinimapUI` 등**: 화면의 특정 좌표에 텍스트를 출력하는 개별 UI 컴포넌트들입니다.

<br>

## 🚀 향후 업데이트 계획 (To-Do)

- [ ] **상태 스택(State Stack) 도입**: Pause, Inventory 창 등을 열고 닫을 때 이전 씬으로 자연스럽게 복귀하는 기능
- [ ] **플리커링(깜빡임) 해결**: `Gotoxy` 호출과 키 입력 위치에 발생하는 미세한 화면 깜빡임 현상 최적화
- [ ] **씬 전환 로직 추가**: Title 씬에서 마을이나 던전 등 다음 씬으로 넘어가는 실질적인 연결
- [ ] **Entity 구조 설계**: 캐릭터(Player), 몬스터(Monster), NPC 등의 공통 속성을 묶는 부모/상속 클래스 구조화
- [ ] **전투 시스템 구현**: 턴제 또는 텍스트 기반의 전투 및 데미지 계산 시스템 추가

<br>

## 📚 학습 기록 및 트러블슈팅 (Study & Log)

프레임워크를 구현하며 발생한 문제, 해결 방식, 그리고 C++ 개념들을 기록합니다.

* 📝 [마이어스 싱글톤, 고정 스텝 게임루프, 게으른 씬 전환 정리](./Study/file1.md)