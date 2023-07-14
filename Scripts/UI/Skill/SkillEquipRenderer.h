#ifndef __SKILL_EQUIP_RENDERER_H__
#define __SKILL_EQUIP_RENDERER_H__

#include "cocos2d.h"
#include "Skill/Skill.h"

USING_NS_CC;

namespace MyGame
{
	class SkillEquipRenderer : public Layer
	{
	public:
		static SkillEquipRenderer* create(Skill* s1, Skill* s2);
		void setS1(Skill* s1);
		void setS2(Skill* s2);
	private:
		bool init(Skill* s1, Skill* s2);
		bool loadComponent();
		bool loadPosition();
	private:
		Skill* _s1, *_s2;
		Sprite* _s1Sprite, * _s2Sprite;
		Label* _talenLb,* _ultiLb;
		DrawNode* _background;
	};
}

#endif // !__SKILL_EQUIP_RENDERER_H__
