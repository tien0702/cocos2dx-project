#ifndef __ENEMY_MOVE_STATE_H__
#define __ENEMY_MOVE_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class BaseStat;
	class EnemyMoveState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		bool checkChasing();
		void updateFlipX();
		void nextMove(const Vec2& pos);
		void flipXOwner(const Vec2& pos);
		BaseStat* _moveSpeedStat;
		BaseStat* _rangeFind;
		MoveTo* _moveTo;
		Node* _target;
		int MoveTag = 4;
	};
}

#endif // !__ENEMY_MOVE_STATE_H__
