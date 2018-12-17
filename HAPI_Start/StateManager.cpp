#include "StateManager.h"
#include "StateMainMenu.h"
#include "StateGame.h"
#include <algorithm>

//StateFacotry
StateManager::StateFactory::StateFactory(StateManager& stateManager)
	: m_stateManager(stateManager), 
	m_stateFactory()
{
	registerNewState<StateGame>(m_stateManager, StateType::Game);
	registerNewState<StateMainMenu>(m_stateManager, StateType::MainMenu);
}

std::unique_ptr<StateBase> StateManager::StateFactory::getState(StateType type) const
{
	auto iter = m_stateFactory.find(type);
	assert(iter != m_stateFactory.cend());
	return iter->second();
}

//StateManager
StateManager::StateManager()
	:m_stateFactory(*this)
{}

StateType StateManager::getCurrentStateType() const
{
	assert(!m_states.empty());
	return m_states.front()->getType();
}

void StateManager::switchToState(StateType type)
{
	//Do not allow to switch to the same state
	if (m_states.empty())
	{
		createCurrentState(type);
		return;
	}

	assert(m_states.front()->getType() != type);

	//Search through available states to then make current
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->get()->getType() == type)
		{
			std::iter_swap(m_states.begin(), iter);
			return;
		}
	}
	
	//If can't find state to switch to, create new
	createCurrentState(type);
}

void StateManager::removeState(StateType type)
{
	auto iter = std::find_if(m_removals.begin(), m_removals.end(), [type](StateType removal) { return removal == type; });
	assert(iter == m_removals.cend());
	m_removals.push_back(type);
}

void StateManager::update()
{
	assert(!m_states.empty());

	m_states.front()->update();
	handleRemovals();
}

void StateManager::draw() const
{
	assert(!m_states.empty());

	for (const auto& state : m_states)
	{
		state->draw();
	}
}

void StateManager::handleRemovals()
{
	for (auto iter = m_removals.cbegin(); iter != m_removals.cend(); ++iter)
	{
		auto state = std::find_if(m_states.begin(), m_states.end(), [iter](const auto& state) { return *iter == state->getType(); });
		assert(state != m_states.cend());
		m_states.erase(state);
	}

	m_removals.clear();
}


bool StateManager::isStateActive(StateType stateType) const
{
	auto iter = std::find_if(m_states.cbegin(), m_states.cend(), [stateType](const auto& state) { return stateType == state->getType(); });
	return (iter != m_states.cend() ? true : false);
}

void StateManager::createCurrentState(StateType type)
{
	m_states.push_front(m_stateFactory.getState(type));
}