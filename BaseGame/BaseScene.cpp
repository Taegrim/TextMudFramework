#include "BaseScene.h"
#include "GameManager.h"

void BaseScene::ChangeScene(SceneType scene)
{
	Event ev;
	ev.type = EventType::ChangeScene;
	ev.next_scene = scene;
	
	GameManager::GetInstance().PushEvent(ev);
}