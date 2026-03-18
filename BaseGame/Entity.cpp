#include "Entity.h"

Entity::Entity(std::string_view name, std::string_view img) : name(name), image(img)
{
}

std::string_view Entity::GetName() const
{
	return name;
}

std::string_view Entity::GetImg() const
{
	return image;
}

bool Entity::IsVisible() const
{
	return is_visible;
}

void Entity::SetName(std::string_view name)
{
	this->name = name;
}

void Entity::SetImage(std::string_view img)
{
	this->image = img;
}

void Entity::SetVisible(bool value)
{
	is_visible = value;
}