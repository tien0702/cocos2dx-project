#include "EnemyStateMachine.h"
#include "Enemy/Enemy.h"
#include "Enemy/State/EnemyTransitionState.h"

bool MyGame::EnemyStateMachine::init(Enemy* owner, std::string defaultStateName, EnemyState* defaultState)
{
	if (!Node::init()) {
		return false;
	}

	this->_owner = owner;
	this->_currentStateName = defaultStateName;

	_states.insert(std::pair<std::string, EnemyState*>(defaultStateName, defaultState));

	return true;
}

void MyGame::EnemyStateMachine::addState(std::string name, EnemyState* state)
{
	_states.insert(std::pair<std::string, EnemyState*>(name, state));
}

void MyGame::EnemyStateMachine::removeState(std::string name)
{
	_states.erase(name);
}

void MyGame::EnemyStateMachine::setState(std::string name)
{
	_states.at(_currentStateName)->exit();
	_currentStateName = name;
	_states.at(_currentStateName)->enter(_owner);
}

void MyGame::EnemyStateMachine::exit()
{
	_currentStateName = "spawn";
}

void MyGame::EnemyStateMachine::enter(Enemy* owner)
{
	_owner = owner;
	_currentStateName = "spawn";
	_states.at(_currentStateName)->enter(_owner);
	_owner->setAnimation("spawn");
	this->scheduleUpdate();
}

MyGame::EnemyState* MyGame::EnemyStateMachine::getCurrentState()
{
	return _states[_currentStateName];
}

void MyGame::EnemyStateMachine::update(float dt)
{
	std::string stateName = _states.at(_currentStateName)->updateState(dt);

	if (stateName == "")
	{
		this->unscheduleUpdate();
		return;
	}

	if (_currentStateName != stateName) {
		// old state
		_states.at(_currentStateName)->exit();
		// change state
		_currentStateName = stateName;
		// new state
		_states.at(_currentStateName)->enter(_owner);
	}
}
