#ifndef __SKILL_DETAIL_RENDERER_H__
#define __SKILL_DETAIL_RENDERER_H__

#include "cocos2d.h"
#include "Skill/Skill.h"
#include "SkillEquipRenderer.h"
USING_NS_CC;

namespace MyGame
{
	class SkillDetailRenderer : public Layer
	{
	public:
		static SkillDetailRenderer* create(Size layerSize);
		void render(Skill* skill, SkillEquipRenderer* equipRender);

	private:
		bool init(Size layerSize);
		bool loadComponent();
		bool loadPosition();
		void loadDescription(Skill* skill);
	private:
		TTFConfig _font;
		Label* _skillNameStr, * _skillDetails;
		Size _layerSize;
		DrawNode* _background;

		ui::Button* _equipBtn;
	};
}

#endif // !__SKILL_DETAIL_RENDERER_H__
