#pragma once
#include "Entity.h"

class NPC : public Entity
{
public:
	NPC(std::string_view name, std::string_view img) : Entity(name, img) {}

	void Render() override;
};

