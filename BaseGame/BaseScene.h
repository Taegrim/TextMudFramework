#pragma once
#include "UIManager.h"

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void ChangeScene() = 0;

protected:
	UIManager ui_manager;
};

