#pragma once

#include "StateType.h"

class Window;
class StateManager;
class StateBase
{
public:
	StateBase(StateManager& stateManager, StateType stateType)
		: m_stateManager(stateManager),
		m_stateType(stateType)
	{}
	StateBase(const StateBase&) = delete;
	StateBase& operator=(const StateBase&) = delete;
	StateBase(StateBase&&) = delete;
	StateBase&& operator=(StateBase&&) = delete;

	StateType getType() const { return m_stateType; }
	
	virtual void update(float deltaTime) = 0;
	virtual void draw(const Window& window) const = 0;
	
private:
	StateManager& m_stateManager;
	const StateType m_stateType;
};