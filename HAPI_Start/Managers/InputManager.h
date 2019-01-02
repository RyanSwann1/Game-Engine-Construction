#pragma once

#include "../States/StateType.h"
#include <functional>
#include <HAPI_InputCodes.h>
#include "../KeyCommand.h"
#include <string>
#include <vector>

enum class KeyBind
{
	LeftArrow = HK_LEFT,
	RightArrow = HK_RIGHT,
	UpArrow = HK_UP,
	DownArrow = HK_DOWN,
	Escape = HK_ESCAPE
};

class HAPI_TKeyboardData;
class StateManager;
class InputManager
{
	class Binding
	{
	public:
		Binding(const std::function<void()>& callBack, KeyCommandName name, StateType owningState, KeyBind keyBind);

		KeyCommandName m_name;
		StateType m_owningStateType;
		std::function<void()> m_callBack;
		KeyBind m_keyBind;
	};

public:
	static InputManager& getInstance()
	{
		static InputManager instance;
		return instance;
	}
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager&& operator=(InputManager&&) = delete;
	
	void registerBinding(const std::function<void()>& callBack, KeyCommandName name, StateType owningState, KeyBind keyBind);
	void unregisterBinding(KeyCommandName name);
	void update() const;

private:
	InputManager();
	std::vector<Binding> m_bindings;
};