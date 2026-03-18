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
	bool IsVisible() const;

	void SetName(std::string_view name);
	void SetImage(std::string_view img);
	void SetVisible(bool value);

protected:
	std::string name;
	std::string image;
	bool is_visible = true;
};

