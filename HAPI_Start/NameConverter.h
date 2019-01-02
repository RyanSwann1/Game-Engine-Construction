#pragma once

#include <string>
#include <unordered_map>
#include <assert.h>
#include <utility>

template <class T>
class NameConverter
{
public:
	const std::pair<std::string, T>& getConvertedName(const std::string& name) const
	{
		auto iter = m_names.find(name);
		assert(iter != m_names.cend());
		return iter;
	}

protected:
	const std::unordered_map<std::string, T> m_names;

	NameConverter(std::unordered_map<std::string, T>&& names)
		: m_names(std::move(names))
	{}
};