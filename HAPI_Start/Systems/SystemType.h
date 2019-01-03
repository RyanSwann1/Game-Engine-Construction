#pragma once

enum class SystemType
{
	Drawable = 0,
	Position,
	Player,
	Movable,
	Total,
	Global
};

constexpr size_t TotalSystems = static_cast<size_t>(SystemType::Total);