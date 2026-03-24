#pragma once
#include "BaseScene.h"

class BattleManager;
class Monster;

enum class BattleState {
	Act,
	TargetEnemy,
	TargetFriendly
};

class BattleScene : public BaseScene
{
public:
	BattleScene() = default;

	void Init() override;
	void SetUI() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;

private:
	BattleManager* bm = nullptr;
	std::vector<Monster*> monster_list;
	BattleState current_state = BattleState::Act;
};

