#pragma once
#include "common.h"

class BaseUI;
class Player;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene() = default;

	virtual void Init() = 0;
	virtual void ProcessEvent(const Event& e) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;		//	배경, 캐릭터 등의 render
	virtual void RenderUI();		//	씬 전용 UI
	virtual void Release() = 0;
	virtual void SetUI() {}		// 씬 전용 로컬 UI 세팅
	virtual void SetMenu() {}	// 선택지 메뉴 세팅

	void AddLocalMessage(SceneUIType type, std::string_view msg);
	void ChangeScene(SceneType scene);
	void PushScene(SceneType scene);
	void PopScene();
	BaseUI* GetLocalUI(SceneUIType type);
	bool IsOpaque() const;

protected:
	std::array<std::unique_ptr<BaseUI>, static_cast<int>(SceneUIType::COUNT)> ui_list;
	bool is_opaque = true;
	Player* player = nullptr;
};

