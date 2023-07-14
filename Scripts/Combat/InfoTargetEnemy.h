#ifndef __INFO_TARGET_ENEMY_H__
#define __INFO_TARGET_ENEMY_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Entity/EntityObserver.h"

USING_NS_CC;

namespace MyGame
{
	class Enemy;
	class HUDlayer;

	class InfoTargetEnemy : public Layer, public EntityObserver
	{
	public:
		static InfoTargetEnemy* getIns();
		virtual void changeTarget(Enemy* enemy);
		virtual void onDead();
		virtual void onDie();
		virtual void onTakingDamage();
		virtual void onTakeDame();
	private:
		static InfoTargetEnemy* _instance;
		HUDlayer* _hublayer;
		Enemy* _targetEnemy;
		Sprite* _bgHealthBar;
		Sprite* _targetIcon;

		ui::LoadingBar* _healthBar;
		TTFConfig _font;
		Label* _targetInfo;
		Label* _infoHp;
	private:
		InfoTargetEnemy();
		virtual bool init();
		virtual void updateInfo();
	};
}

#endif // !__INFO_TARGET_ENEMY_H__
