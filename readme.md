# 🛡️ C++ Text MUD Game Framework

본 프로젝트는 C++17 이상을 기반으로 작성된 **콘솔 텍스트 기반 MUD 게임 전용 프레임워크**입니다.

<br>

## 🗂️ 클래스 구조 (Architecture)
<img width="2065" height="1234" alt="UML" src="https://github.com/user-attachments/assets/60c2dda7-a86e-4b04-94bd-fe75562b1cc3" />


### **Core & Management**
* **`GameManager`**: 메인 루프 실행, 이벤트 큐 관리 및 **상태 스택(Scene Stack)** 기반의 씬 전환을 담당하는 핵심 엔진입니다.
* **`UIManager`**: **더블 버퍼링(Double Buffering)** 기법을 사용하여 콘솔 깜빡임을 최소화하고, 모든 UI 컴포넌트의 렌더링과 가시성을 관리합니다.

### **Entity**
* **`Entity` / `NPC`**: 이름과 이미지를 가진 모든 게임 내 객체의 최상위 추상 클래스 및 비전투형 클래스입니다.
* **`BattleEntity` / `Player`, `Monster`**: 전투 기능을 가진 클래스이며, **`Status`** 클래스로 능력치를 관리합니다.
* **`Status`**: HP, MP, 공격력, 방어력 등 모든 스탯 데이터를 처리합니다.

### **Scene & UI System**
* **`BaseScene` / `TitleScene`, `TownScene`**: 게임의 각 상태(화면)를 정의하는 추상 클래스 및 그 구현체입니다. 
* **`BaseUI` / `ScreenUI`, `LogUI`, `MinimapUI` 등**: 화면의 특정 좌표에 텍스트를 출력하는 개별 UI 컴포넌트들입니다.

<br>

## 🚀 향후 업데이트 계획 (To-Do)
- **씬 상태 스택 수정**: 씬 렌더를 레이어 방식으로 변경(씬 겹치기)
- **전투 시스템**: 턴제 기반의 전투 시스템 및 데미지 계산 로직 구현
- **인벤토리**: 캐릭터의 아이템 소지 및 장착 시스템 구현
- **상점**: 상인 NPC 추가 및 물건 구매/판매 기능 구현
- **파일 입출력**: 플레이어 세이브 데이터 및 몬스터 정보의 파일 처리
- **사운드 시스템**: 게임 몰입도를 높이기 위한 배경음 및 효과음 추가

<br>

## 📚 학습 기록 및 트러블슈팅 (Study & Log)

프레임워크를 구현하며 발생한 문제, 해결 방식, 그리고 C++ 개념들을 기록합니다.

* 📝 [마이어스 싱글톤, 고정 스텝 게임루프, 게으른 씬 전환 정리](./Study/file1.md)