#include "CharacterStateMachine.h"
#include "Manager/GameManager.h"


bool MyGame::CharacterStateMachine::init(Character* character, std::string name, CharacterState* defaultState)
{
	if (!Node::init()) {
		log("init CharacterStateMachine failed!");
		return false;
	}

	_character = character;
	_currentStateName = name;
	_states.insert(std::pair<std::string, CharacterState*>(name, defaultState));
	_states.at(name)->enter(_character);

	this->scheduleUpdate();
	return true;
}

std::string MyGame::CharacterStateMachine::addState(std::string name, CharacterState* state)
{
	_states.insert(std::pair<std::string, CharacterState*>(name, state));
	return "";
}

void MyGame::CharacterStateMachine::removeState(std::string name)
{
	_states.erase(name);
}

void MyGame::CharacterStateMachine::setState(std::string name)
{
	_states.at(_currentStateName)->exit();
	_currentStateName = name;
	_states.at(_currentStateName)->enter(_character);
}

MyGame::CharacterState* MyGame::CharacterStateMachine::getCurrentState()
{
	return _states[_currentStateName];
}

void MyGame::CharacterStateMachine::update(float dt)
{
	std::string stateName = _states.at(_currentStateName)->updateState(dt);
	if (stateName == "")
	{
		GameManager::getIns()->getChapter()->sumaryChap(false);
		return;
	}
	
	if (_currentStateName != stateName) {
		// old state
		_states.at(_currentStateName)->exit();
		// change state
		_currentStateName = stateName;
		// new state
		_states.at(_currentStateName)->enter(_character);
	}
}
