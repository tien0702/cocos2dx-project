#ifndef __PASSIVE_SKILL_H__
#define __PASSIVE_SKILL_H__

#include "Skill/ISkill.h"
#include "Entity/EntityObserver.h"
#include "Entity/Bonus.h"

namespace MyGame
{
	class Entity;
	class PassiveSkill : public ISkill, public EntityObserver, public Sprite
	{
	public:
		PassiveSkill();
		virtual bool init();
		virtual void onDead();
		virtual void onTakingDamage();

		void active(Entity* owner);
		void disable();
		void useSkill();
	private:
		CC_SYNTHESIZE(Entity*, _owner, Owner);
		CC_SYNTHESIZE(float, _successRate, SuccessRate);
		CC_SYNTHESIZE(std::list<Bonus*>, _bonuses, Bonuses);

		bool _needUsed;
	private:
		virtual void update(float dt);
	};
}

#endif // !__PASSIVE_SKILL_H__
