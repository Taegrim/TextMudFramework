#pragma once
#include "BaseScene.h"

class DungeonScene : public BaseScene
{
public:
	DungeonScene() = default;

	void SetUI() override;
	void SetMenu() override;

	// BaseScene을(를) 통해 상속됨
	void Init() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;
};

