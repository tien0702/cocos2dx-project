#ifndef __SKILL_LIST_RENDERER_H__
#define __SKILL_LIST_RENDERER_H__

#include "cocos2d.h"
#include "Skill/Skill.h"
#include "ui/CocosGUI.h"
#include "UI/Skill/SkillDetailRenderer.h"
#include "SkillListRenderer.h"

USING_NS_CC;

namespace MyGame
{
	class SkillListRenderer : public Layer
	{
	public:
		static SkillListRenderer* create(std::vector<Skill*>* skills, SkillDetailRenderer* detailRenderer, SkillEquipRenderer* equipRender);

	private:
		bool init(std::vector<Skill*>* skills, SkillDetailRenderer* detailRenderer, SkillEquipRenderer* equipRender);
		std::vector<ui::Button*>* getButtons(std::vector<Skill*>* skills);
		void setupdButtons(std::vector<ui::Button*> buttons);
		ui::ScrollView* createScrollView(std::vector<ui::Button*>* buttons, float distance, Size size);
		void selected(Node* target);
	private:
		std::vector<Skill*>* _skills;
		CC_SYNTHESIZE(SkillDetailRenderer*, _detailRenderer, DetailRenderer);
		Skill* _currentSelect;
		Sprite* _selectedSprite;
		SkillEquipRenderer* _equipRender;
	};
}

#endif // !__SKILL_LIST_RENDERER_H__
