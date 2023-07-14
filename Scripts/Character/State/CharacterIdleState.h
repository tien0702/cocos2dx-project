#ifndef __CHARACTER_IDLE_STATE_H__
#define __CHARACTER_IDLE_STATE_H__

#include "Character/State/CharacterState.h"

namespace MyGame
{
	class Character;
	class CharacterIdleState : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();
		CharacterIdleState();
	private:
		bool initAnimation();
		bool checkMove();
		bool checkPrepareDash();
	};
}

#endif // !__CHARACTER_IDLE_STATE_H__
