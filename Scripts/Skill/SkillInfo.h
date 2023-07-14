#ifndef __SKILL_INFO_H__
#define __SKILL_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	class SkillInfo
	{
	private:
		CC_SYNTHESIZE(int, _skillID, SkillID);
		CC_SYNTHESIZE(std::string, _skillName, SkillName);
		CC_SYNTHESIZE(std::string, _description, Description);
		CC_SYNTHESIZE(std::string, _iconName, IconName);
		CC_SYNTHESIZE(std::string, _effectName, EffectName);
	};
}

#endif // !__SKILL_INFO_H__
