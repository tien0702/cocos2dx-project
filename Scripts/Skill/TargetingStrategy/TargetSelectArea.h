#ifndef __TARGET_SELECT_AREA_H__
#define __TARGET_SELECT_AREA_H__

#include "Skill/TargetingStrategy/TargetingStrategy.h"


namespace MyGame
{
	class TargetSelectArea : public SkillTargeting, public Node
	{
	public:
		bool init();
		void target(Skill* skill);
		void activeSkill(Vec2 position);
	private:
		DrawNode* _rangeVisual;
		DrawNode* _aoERadiusVisual;
	private:
		bool loadRangeVisual();
		bool loadAoERadius();
		void update(float dt);
		Vec2 getDirectionInput() const;
		Vec2 calculatePosition() const;
		void setAtPositionEnemyNeares();
		void updateAoERadius(Vec2 direction) const;
		void reset();

		bool initBody();
		bool onContactBegin(PhysicsContact& contact);

	};
}

#endif // !__TARGET_SELECT_AREA_H__
