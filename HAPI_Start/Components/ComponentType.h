#pragma once

enum class ComponentType
{
	Position = 0,
	Drawable,
	Movable,
	Animation,
	Total
};

constexpr size_t TotalComponents = static_cast<size_t>(ComponentType::Total);