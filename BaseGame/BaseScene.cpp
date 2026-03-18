#include "BaseScene.h"
#include "GameManager.h"
#include "GameUI.h"

BaseScene::BaseScene()
{
	player = GameManager::GetInstance().GetPlayer();
}

void BaseScene::RenderUI()
{
	for (auto& ui : ui_list) {
		if (ui && ui->IsVisible()) {
			ui->Render();
		}
	}
}

void BaseScene::AddLocalMessage(SceneUIType type, std::string_view msg)
{
	int idx = static_cast<int>(type);

	if (idx >= 0 && idx < static_cast<int>(SceneUIType::COUNT)) {
		ui_list[idx]->AddMessage(msg);
	}
}

void BaseScene::ChangeScene(SceneType scene)
{
	Event ev{};
	ev.type = EventType::ChangeScene;
	ev.next_scene = scene;
	
	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PushScene(SceneType scene)
{
	Event ev{};
	ev.type = EventType::PushScene;
	ev.next_scene = scene;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PopScene()
{
	Event ev{};
	ev.type = EventType::PopScene;

	GameManager::GetInstance().PushEvent(ev);
}

BaseUI* BaseScene::GetLocalUI(SceneUIType type)
{
	return ui_list[static_cast<int>(type)].get();
}

bool BaseScene::IsOpaque() const
{
	return is_opaque;
}
