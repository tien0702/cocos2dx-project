#ifndef __SKILL_STATE_MACHINE_H__
#define __SKILL_STATE_MACHINE_H__

#include "cocos2d.h"
#include "SkillState.h"

USING_NS_CC;

namespace MyGame
{
	class Skill;
	class SkillStateMachine : public Node
	{
	public:
		bool init();
		SkillStateMachine(Skill* owner);

		void setDefault(SkillStateType type);
		void setState(SkillStateType type);
		void addState(SkillStateType type, SkillState* newState);
		void removeState(SkillStateType type);
	private:
		Skill* _owner;
		SkillStateType _currentState;
		std::map<SkillStateType, SkillState*> _states;
		void update(float dt);
	};
}

#endif // !__SKILL_STATE_MACHINE_H__
