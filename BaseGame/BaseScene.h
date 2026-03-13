#pragma once
#include "UIManager.h"

class BaseScene
{
public:
	BaseScene(){}
	virtual ~BaseScene() {}

	virtual void Init() = 0;
	virtual void ProcessEvent(const Event& e) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual void ChangeScene(SceneType scene);
};

