#ifndef __CHARACTER_DIE_STATE_H__
#define __CHARACTER_DIE_STATE_H__

#include "Character/State/CharacterState.h"

namespace MyGame
{
	class Character;
	class CharacterDieState : public CharacterState
	{
	public:
		virtual void enter(Character* owner);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		bool initAnimation();
		float _time;
		float _elapsedTime = 0.0f;
	};
}

#endif // !__CHARACTER_DIE_STATE_H__
