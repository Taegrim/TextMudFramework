#include "GameManager.h"
#include "TitleScene.h"

GameManager::GameManager() : scene(nullptr), isRunning(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	scene = new TitleScene();
	scene->Init();
}

void GameManager::Run()
{
	while (isRunning) {
		if (scene) {
			scene->Render();
			scene->Update();
		}
	}
}

void GameManager::Release()
{
	if (scene) {
		scene->Release();

		delete scene;
		scene = nullptr;
	}
}
