#include "InputManager.h"
#include "StateManager.h"
#include <HAPI_InputCodes.h>
#include <HAPI_lib.h>
#include <HAPI_Types.h>
#include <algorithm>

//Binding
InputManager::Binding::Binding(const std::function<void()>& callBack, KeyCommandName name, StateType owningState, KeyBind keyBind)
	: m_name(name),
	m_owningStateType(owningState),
	m_callBack(callBack),
	m_keyBind(keyBind)
{}

//InputManager
InputManager::InputManager()
	:m_bindings(),
	m_callBacks()
{}

void InputManager::registerBinding(const std::function<void()>& callBack, KeyCommandName name, StateType owningState, KeyBind keyBind)
{
	m_bindings.emplace_back(callBack, name, owningState, keyBind);
}

void InputManager::unregisterBinding(KeyCommandName name)
{
	auto iter = std::find_if(m_bindings.begin(), m_bindings.end(), [name](const auto& binding) { return binding.m_name == name; });
	assert(iter != m_bindings.cend());
	m_bindings.erase(iter);
}

void InputManager::update() const
{
	const HAPISPACE::HAPI_TKeyboardData& keyboardData = HAPI.GetKeyboardData();
	std::vector<std::function<void()>> callBacks;
	for (const auto& binding : m_bindings)
	{
		if (keyboardData.scanCode[static_cast<int>(binding.m_keyBind)])
		{
			callBacks.push_back(binding.m_callBack);
		}
	}

	for (const auto& callBack : callBacks)
	{
		callBack();
	}
}