#ifndef __CHARACTER_STATE_UI_H__
#define __CHARACTER_STATE_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Entity/EntityObserver.h"

USING_NS_CC;

namespace MyGame
{
	class EntityHealth;
	class Entity;
	class CharacterStateUI : public Sprite, public EntityObserver
	{
	public:
		virtual bool init();
	protected:
		EntityHealth* _entityHealth;
		Entity* _character;
		TTFConfig _font;

		std::string _bgPath = "Background/bg1.png";
		std::string _HPtrackPath = "Background/HPtrack.png";
		std::string _MPtrackPath = "Background/MPtrack.png";

		std::string _hpProgressPath = "Background/HPprogress.png";
		std::string _mpProgressPath = "Background/MPprogress.png";

		ui::Button* _avatar;
		ui::LoadingBar* _hpBar;
		ui::LoadingBar* _mpBar;
		Label* _levelInfo, * _hpInfo, *_mpInfo;
	protected:
		virtual bool loadProperties();
		void gotoInformationScene();

		// Hp
		virtual void onTakeDame();
		virtual void onRecoveryHP();
		virtual void onReborn();

		// Mp
		virtual void onRecoveryMp();
		virtual void onRebornMp();
		virtual void onTakeMp();

		virtual void updateHP();
		virtual void updateMP();
	};
}

#endif // !__CHARACTER_STATE_UI_H__
