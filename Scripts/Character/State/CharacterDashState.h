#ifndef __CHARACTER_DASH_STATE_H__
#define __CHARACTER_DASH_STATE_H__

#include "Character/State/CharacterState.h"

namespace MyGame
{
	class ActiveSkill;
	class ButtonSkill;
	class BaseStat;
	class GameMap;

	class CharacterDashState : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();
	private:
		bool initAnimation();
		bool loadProperties();
		void dash();

		Vec2 calculateNextPos(float time);
		Vec2 getGroundPosOwner()const;
		void handleMoveMeta(int metaType, Vec2 vel);
		void handleMove();
	private:
		ActiveSkill* _ability;
		ButtonSkill* _targetInput;
		BaseStat* _dashSpeed;
		GameMap* _map;

		int _currentCount;
		float _elapsedTime = 0.0f;
		float _castingTime;
	};
}

#endif // !__CHARACTER_DASH_STATE_H__
