#ifndef __ENEMY_OBSERVER_H__
#define __ENEMY_OBSERVER_H__

namespace MyGame
{
	class EntitySubject;
	class EntityObserver
	{
	public:
		// Hp
		virtual void onRecoveryHP() {}
		virtual void onRebornHp() {}
		virtual void onTakeDame() {}
		virtual void onDie() {}

		// Mp
		virtual void onRecoveryMp() {}
		virtual void onRebornMp() {}
		virtual void onTakeMp() {}
	protected:
		EntitySubject* _subject;
	};
}

#endif // !__ENEMY_OBSERVER_H__
