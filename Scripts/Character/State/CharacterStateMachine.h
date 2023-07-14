#ifndef __CHARACTER_STATE_MACHINE_H__
#define __CHARACTER_STATE_MACHINE_H__


#include "cocos2d.h"
#include "Character/Character.h"
#include "Character/State/CharacterState.h"

USING_NS_CC;

namespace MyGame
{
	class Character;
	class CharacterStateMachine : public Node
	{
	public:
		bool init(Character* character, std::string name, CharacterState* defaultState);
		std::string addState(std::string name, CharacterState* state);
		void removeState(std::string name);

		void setState(std::string name);
		CharacterState* getCurrentState();
	private:
		void update(float dt);
		std::map<std::string, CharacterState*> _states;
		std::string _currentStateName;
		Character* _character;
	};
}

#endif // !__CHARACTER_STATE_MACHINE_H__
