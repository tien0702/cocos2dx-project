#ifndef __ENEMY_STATE_MACHINE_H__
#define __ENEMY_STATE_MACHINE_H__


#include "cocos2d.h"
#include "Enemy/State/EnemyState.h"

USING_NS_CC;

namespace MyGame
{
	class Enemy;
	class EnemyStateMachine : public Node
	{
	public:
		static const int Idle = 1;
		static const int Run = 2;
		static const int Attack = 3;
		static const int Chasing = 3;

		virtual bool init(Enemy* owner, std::string defaultStateName, EnemyState* defaultState);
		virtual void addState(std::string name, EnemyState* state);
		virtual void removeState(std::string name);
		virtual void setState(std::string name);
		virtual void exit();
		virtual void enter(Enemy* owner);
		EnemyState* getCurrentState();
	protected:
		virtual void update(float dt);
		std::map<std::string, EnemyState*> _states;
		std::string _currentStateName;

		Enemy* _owner;
	};
}

#endif // !__ENEMY_STATE_MACHINE_H__
