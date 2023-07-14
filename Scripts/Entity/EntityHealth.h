#ifndef __ENTITY_HEALTH_H__
#define __ENTITY_HEALTH_H__

#include "cocos2d.h"
#include "DamagerSystem/DamageMessage.h"

USING_NS_CC;

namespace MyGame
{
	class BaseStat;
	class Entity;
	class EntityHealth : public Node
	{
	public:
		static const int TimeRecovery = 5000;

		bool init();
		void update(float dt);
		void takeDamage(DamageMessage* data);
		void reborn();
		void recovery(int hp);
		bool isDead();
	private:
		CC_SYNTHESIZE(BaseStat*, _maxHp, MaxHp);
		CC_SYNTHESIZE(BaseStat*, _hp, Hp);
		CC_SYNTHESIZE(BaseStat*, _hpRecovery, HpRecovery);
		CC_SYNTHESIZE(Entity*, _owner, Owner);
		CC_SYNTHESIZE(float, _invulnerabiltyTime, InvulnerabiltyTime);
		CC_SYNTHESIZE(float, _timeSinceLastHit, TimeSinceLastHit);
		CC_SYNTHESIZE(bool, _isInvulnerable, IsInvulnerable);
	};
}

#endif // !__ENTITY_HEALTH_H__
