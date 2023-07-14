#ifndef __CHARACTER_SPAWN_STATE_H__
#define __CHARACTER_SPAWN_STATE_H__

#include "Character/State/CharacterState.h"

namespace MyGame
{
	class Character;
	class CharacterSpawnState : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();
		CharacterSpawnState();
	private:
		bool initAnimation();
		void setup();
		float _spawnTime;
		float _elapsedTime;
	};
}

#endif // !__CHARACTER_SPAWN_STATE_H__
