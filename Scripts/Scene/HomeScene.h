#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Scene/WorldMap.h"

USING_NS_CC;

namespace MyGame
{
	enum HomeOption
	{
		StartGame,
		SettingGame,
		ExitGame,
		TotalOption
	};

	class HomeScene : public Scene
	{
	public:
		virtual bool init();
		CREATE_FUNC(HomeScene);
	private:
		Sprite* _background;
		ui::Button* _options[HomeOption::TotalOption];
		const char* _optionName[HomeOption::TotalOption] = { "START", "SOUND SETTINGS", "EXIT"};
		const char* _nameGame = "Luna's Chronicles";
		TTFConfig _font;
		bool loadProperties();
		void loadPostion();
		void loadEventForButton();
		void gotoWorldMap();

	private:
		Label* _gameNameLB;
	};
}

#endif // !__HOME_SCENE_H__
