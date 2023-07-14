#include "SkillStateMachine.h"

bool MyGame::SkillStateMachine::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	return true;
}

MyGame::SkillStateMachine::SkillStateMachine(Skill* owner)
{
	_owner = owner;
}

void MyGame::SkillStateMachine::setDefault(SkillStateType type)
{
	_currentState = type;
	if (_states.find(_currentState) != _states.end())
	{
		_states[_currentState]->enter(_owner);
	}
	else
	{
		log("skill state type %d is null!", (int)type);
	}
}

void MyGame::SkillStateMachine::setState(SkillStateType type)
{
	if (type == _currentState) return;
	if (_states.find(_currentState) != _states.end()) _states[_currentState]->exit();
	_currentState = type;
	_states[_currentState]->enter(_owner);
}

void MyGame::SkillStateMachine::addState(SkillStateType type, SkillState* newState)
{
	if (_states.find(type) == _states.end() && newState != nullptr)
	{
		auto newElement = std::pair<SkillStateType, SkillState*>(type, newState);
		_states.insert(newElement);
	}
	else
	{
		log("Error insert new skill state!");
	}
}

void MyGame::SkillStateMachine::removeState(SkillStateType type)
{
	if (_states.find(type) == _states.end())
	{
		_states.erase(type);
	}
}

void MyGame::SkillStateMachine::update(float dt)
{
	// 
	SkillStateType type = _states[_currentState]->excute(dt);
	if (type != _currentState) this->setState(type);

}
