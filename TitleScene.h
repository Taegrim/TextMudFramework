#pragma once
#include "BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene();
	virtual ~TitleScene();


	// BaseScene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void ChangeScene() override;

};

