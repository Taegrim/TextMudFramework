#pragma once
#include "common.h"

class Entity
{
public:
	Entity(std::string_view name, std::string_view img);
	virtual ~Entity() = default;

	virtual void Render() = 0;

	std::string_view GetName() const;
	std::string_view GetImg() const;

	void SetName(std::string_view name);
	void SetImage(std::string_view img);

protected:
	std::string name;
	std::string image;
};

