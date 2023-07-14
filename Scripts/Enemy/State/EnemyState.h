#ifndef __ENEMY_STATE_H__
#define __ENEMY_STATE_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Enemy;
	class EnemyState
	{
	public:
		virtual void enter(Enemy* enemy) = 0;
		virtual std::string updateState(float dt) = 0;
		virtual void exit() = 0;
	protected:
		CC_SYNTHESIZE(int, _idState, IDState);
		Enemy* _owner;
		Animate* _animate;
	};
}

#endif // !__ENEMY_STATE_H__
