#pragma once

#include "../States/StateBase.h"
#include <memory>
#include <assert.h>
#include <functional>
#include <unordered_map>
#include <list>
#include <vector>

class StateManager
{
	class StateFactory
	{
	public:
		StateFactory(StateManager& stateManager);
		StateFactory(const StateFactory&) = delete;
		StateFactory& operator=(const StateFactory&) = delete;
		StateFactory(StateFactory&&) = delete;
		StateFactory&& operator=(StateFactory&&) = delete;
	
		std::unique_ptr<StateBase> getState(StateType type) const;

	private:
		StateManager& m_stateManager;
		std::unordered_map<StateType, std::function<std::unique_ptr<StateBase>()>> m_stateFactory;

		template <class State>
		void registerNewState(StateManager& stateManager, StateType type)
		{
			assert(m_stateFactory.find(type) == m_stateFactory.cend());
			m_stateFactory.emplace(type, [&stateManager, type]() -> std::unique_ptr<State>
			{
				return std::make_unique<State>(stateManager, type);
			});
		}
	};

public:
	StateManager();
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;
	StateManager&& operator=(StateManager&&) = delete;
	StateManager(StateManager&&) = delete;

	StateType getCurrentStateType() const;
	void switchToState(StateType type);
	void removeState(StateType type);

	void update();
	void draw() const;

private:
	const StateFactory m_stateFactory;
	std::list<std::unique_ptr<StateBase>> m_states;
	std::list<StateType> m_removals;
	
	void handleRemovals();
	bool isStateActive(StateType type) const;
	void createCurrentState(StateType type);
};