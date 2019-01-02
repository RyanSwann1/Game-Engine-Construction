#include "EntityNameConverter.h"

std::unordered_map<std::string, EntityName> initializeEntityNames()
{
	std::unordered_map<std::string, EntityName> entityNames;
	entityNames.reserve(static_cast<size_t>(EntityName::Total));
	entityNames.emplace("Player", EntityName::Player);
	entityNames.emplace("Enemy", EntityName::Enemy);
	entityNames.emplace("Projectile", EntityName::Projectile);

	return entityNames;
}

EntityNameConverter::EntityNameConverter()
	: NameConverter(initializeEntityNames())
{}
