#ifndef __HP_BAR_VISUAL_H__
#define __HP_BAR_VISUAL_H__

#include "cocos2d.h"
#include "Entity/Entity.h"
#include "ui/CocosGUI.h"
#include "Entity/EntityObserver.h"

USING_NS_CC;

namespace MyGame
{
	class HPBarVisual : public Sprite, public EntityObserver
	{
	public:
		virtual bool init();
		virtual void active(Entity* owner);
		virtual void disable();
	protected:
		virtual bool loadProperties();
		virtual void updateHPBar();

		virtual void registration();
		virtual void cancelRegistration();
		virtual void addToPool();

		virtual float calculatePercent();
		virtual Vec2& calculatePostion();

		// Override
		virtual void onRecoveryHP() override;
		virtual void onRebornHp() override;
		virtual void onTakeDame() override;
		virtual void onDie() override;
	protected:
		CC_SYNTHESIZE(Entity*, _owner, Owner);
		CC_SYNTHESIZE(ui::LoadingBar*, _hpBar, HPBarLoading);
		CC_SYNTHESIZE(Sprite*, _hpBarBG, HPBarBG);
	};
}

#endif // !__HP_BAR_VISUAL_H__
