#ifndef __CHARACTER_MOVE_STATE_H__
#define __CHARACTER_MOVE_STATE_H__

#include "Character/State/CharacterState.h"


namespace MyGame
{
	class Character;
	class BaseStat;
	class GameMap;
	class CharacterMoveState : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();
	private:
		bool initAnimation();
		bool loadProperties();
	private:
		BaseStat* _moveSpeed;

		GameMap* _map;
		float _accelRate = 1;
		float _scaleFactor = 1.0f;
		bool _enable = true;

		void handleMoveMeta(int metaType, Vec2 vel);
		void updateFlipX(Vec2 dir);
		Vec2 calculateVelocity();
		Vec2 calculateNextPos(float time);
		Vec2 getGroundPosOwner()const;
		Vec2 getHeadPosOwner()const;

		void move(float dt);
		bool canMove();
		bool checkPrepareDash();
	};
}

#endif // !__CHARACTER_MOVE_STATE_H__
