#ifndef __CHARACTER_STATE_H__
#define __CHARACTER_STATE_H__

#include "cocos2d.h"

USING_NS_CC;


namespace MyGame
{
	class Character;
	class CharacterState
	{
	public:
		virtual void enter(Character* owner) = 0;
		virtual std::string updateState(float dt) = 0;
		virtual void exit() = 0;
	protected:
		CC_SYNTHESIZE(int, _idState, IDState);
		Character* _owner;
	};
}

#endif // !__CHARACTER_STATE_H__
