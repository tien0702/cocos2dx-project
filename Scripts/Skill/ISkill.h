#ifndef __I_SKILL_H__
#define __I_SKILL_H__

#include "cocos2d.h"

namespace MyGame
{
	class ISkill
	{
	public:
		void setCondition(std::pair<int, std::string> condition) { this->_condition = condition; }
		std::pair<int, std::string> getCondition() { return this->_condition; }
	protected:
		CC_SYNTHESIZE(int, _level, Level);
		CC_SYNTHESIZE(std::string, _skillName, SkillName);
		CC_SYNTHESIZE(std::string, _description, Description);

		CC_SYNTHESIZE(float, _cooldown, Cooldown);
		std::pair<int, std::string> _condition;
		//
		float _elapsedTime;
	};
}

#endif // !__I_SKILL_H__
