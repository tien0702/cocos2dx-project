#ifndef __SETTING_SCENE_IN_GAME_H__
#define __SETTING_SCENE_IN_GAME_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

namespace MyGame
{
	class SettingSceneInGame : public Scene
	{
	public:
		bool init();

		bool loadComponents();
		bool loadProperties();
		bool loadButtonComponent();
		bool loadSliderComponent();
		CREATE_FUNC(SettingSceneInGame);
	private:
		TTFConfig _font;

		ui::Slider* _backgroundMusic, * _soundEffectVolume;
		ui::Button* _backBtn, *_goHomeBtn;

		Sprite* _background;
	};
}

#endif // !__SETTING_SCENE_IN_GAME_H__
