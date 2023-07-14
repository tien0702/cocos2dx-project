#ifndef __SKILL_EQUIPPED_RENDERER_H__
#define __SKILL_EQUIPPED_RENDERER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Skill/Skill.h"

USING_NS_CC;

namespace MyGame
{
	class SkillBtnShowDetail : public ui::Button
	{
	public:
		bool init();
	private:
		CC_SYNTHESIZE(Skill*, _skillTarget, SkillTarget);
		Sprite* getDescription();
		TTFConfig _font;
	};
}

#endif // !__SKILL_EQUIPPED_RENDERER_H__
