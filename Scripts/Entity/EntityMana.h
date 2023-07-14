#ifndef __ENTITY_MANA_H__
#define __ENTITY_MANA_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Entity;
	class EntityMana : public Node
	{
	public:
		static const int TimeRecovery = 5000;
		bool init();
		void update(float dt);
		bool takeMana(int amount);
		void recovery(int amount);
		void reborn();
	public:
		CC_SYNTHESIZE(Entity*, _owner, Owner);
	};
}

#endif // !__ENTITY_MANA_H__
