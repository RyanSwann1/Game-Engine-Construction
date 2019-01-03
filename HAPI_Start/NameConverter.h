#pragma once

#include <string>
#include <unordered_map>
#include <assert.h>
#include <utility>

template <class ConvertedName>
class NameConverter
{
public:
	ConvertedName getConvertedName(const std::string& name) const
	{
		auto iter = m_names.find(name);
		assert(iter != m_names.cend());
		return iter->second;
	}

protected:
	const std::unordered_map<std::string, ConvertedName> m_names;

	NameConverter(std::unordered_map<std::string, ConvertedName>&& names)
		: m_names(std::move(names))
	{}
};