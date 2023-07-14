#ifndef __CHARACTER_ATTACK_STATE_H__
#define __CHARACTER_ATTACK_STATE_H__

#include "Character/State/CharacterState.h"

namespace MyGame
{
	class BaseStat;
	class CharacterAttackState : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();
	private:
		bool initAnimation();
		bool loadProperties();
	private:
		float _castingTime = 0.0f;
		float _elapsedTime = 0.0f;

		BaseStat* _attackSpeed;
	};
}

#endif // !__CHARACTER_ATTACK_STATE_H__
