#ifndef __TARGET_PROJETILE_H__
#define __TARGET_PROJETILE_H__

#include "TargetingStrategy.h"

namespace MyGame
{
	class TargetProjectile : public SkillTargeting, public Node
	{
	public:
		bool init();
		void target(Skill* skill);
		void activeSkill(Vec2 position);
	private:
		void update(float dt);
		void updateDirectionVisual();
		void reset();
		void changeStateToCooldown();
		void drawDirection();
		void rotateToEnemyNeares();

		float calculateRotation(Vec2 direction);
		Vec2 getInputDirection();
		Vec2 calculateDirection();
		Vec2 calculatePosition();
	private:
		DrawNode* _directionVisual;
	};
}

#endif // !__TARGET_PROJETILE_H__
