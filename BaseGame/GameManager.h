#pragma once
#include "BaseScene.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Init();
    void Run();
    void Release();

private:
	BaseScene* scene;
	bool isRunning;
};

