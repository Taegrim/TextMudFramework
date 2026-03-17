#pragma once
#include "common.h"

class BaseScene
{
public:
	BaseScene() = default;
	virtual ~BaseScene() = default;

	virtual void Init() = 0;
	virtual void ProcessEvent(const Event& e) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	void ChangeScene(SceneType scene);
};

