#include "BattleEntity.h"

BattleEntity::BattleEntity(std::string_view name, std::string_view img, const Status& stat)
	: Entity(name, img), status(stat)
{
}

const Status& BattleEntity::GetStatus() const
{
	return status;
}

Status& BattleEntity::GetStatus()
{
	return status;
}
