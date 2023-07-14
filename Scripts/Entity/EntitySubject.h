#ifndef __ENEMY_SUBJECT_H__
#define __ENEMY_SUBJECT_H__

#include "cocos2d.h"

using namespace std;

namespace MyGame
{
	enum class EntityObserverType
	{
		// HP
		OnTakeDame,
		OnDie,
		OnRebornHP,
		OnRecoveryHP,
		// MP
		OnTakeMP,
		OnRecoveryMP,
		OnRebornMP
	};

	class EntityObserver;

	typedef void (EntityObserver::* NotifyObserverCallBack)();
	class EntitySubject
	{
	public:
		virtual void attach(EntityObserverType type, EntityObserver* ob);
		virtual void dettach(EntityObserverType type, EntityObserver* ob);
		virtual void notifyAllObserver(EntityObserverType type);
		virtual void dettachAllObject();
	protected:
		NotifyObserverCallBack getObserverCallbackByType(EntityObserverType type);
	protected:
		map<EntityObserverType, list<EntityObserver*>*> _observers;
	};
}

#endif // !__ENEMY_SUBJECT_H__
