#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

namespace MyGame
{
	class SettingScene : public Scene
	{
	public:
		bool init();
		CREATE_FUNC(SettingScene);
	private:
		bool loadComponents();
		bool loadProperties();

		bool loadButtonComponent();
		bool loadSliderComponent();
	private:
		TTFConfig _font;

		ui::Slider* _backgroundMusic, *_soundEffectVolume;
		ui::Button*_backBtn;

		Sprite* _background;
	};
}

#endif // !__SETTING_SCENE_H__
