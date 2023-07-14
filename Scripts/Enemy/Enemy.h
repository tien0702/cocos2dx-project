#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity/Entity.h"
#include "Entity/EntitySubject.h"
#include "Enemy/State/EnemyStateMachine.h"

namespace MyGame
{
	enum class EnemyID
	{
		SlimeID
	};

	class Enemy : public Entity
	{
	public:
		virtual bool init();
	public:
		virtual void takeDamage(DamageMessage* data);

	public: // Get - Set
		virtual int getCurrentStateID();
		void spawn();
		void enableRangeVisual(bool enable);
	protected:
		DrawNode* _rangeFindVisual;
		Label* _infoLv;
		CC_SYNTHESIZE(Rect, _spawnArea, EnemySpawnArea);
		CC_SYNTHESIZE(EnemyStateMachine*, _stateMachine, EStateMachine);
	protected:
		virtual bool loadProperties();
		virtual bool initAnimation();
		virtual bool initBody();
		virtual bool loadComponent();
		virtual bool loadInfo();
		virtual void update(float dt);
		virtual void die();
		bool onContactBegin(PhysicsContact& contact);
	};
}

#endif // !__ENEMY_H__
