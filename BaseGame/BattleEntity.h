#pragma once
#include "Entity.h"
#include "Status.h"

class BattleEntity : public Entity
{
public:
	BattleEntity(std::string_view name, std::string_view img, const Status& stat);

	virtual void Render() = 0;
	
	int TakeDamage(int dmg);
	bool IsDead() const;

	const Status& GetStatus() const;
	Status& GetStatus();
	int GetHp() const;

protected:
	Status status;
};

