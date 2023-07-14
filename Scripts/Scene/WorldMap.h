#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Chapter/ChapterInfo.h"
#include "Chapter/LocationInfoBtn.h"
#include "Chapter/ChapterInforRenderer.h"
#include "UI/CoinBar.h"

USING_NS_CC;

namespace MyGame
{
	class WorldMap : public Scene
	{
	public:
		virtual bool init();
		CREATE_FUNC(WorldMap);
	private:
		ui::Button* _backBT;
		ui::Button* _attackBtn, *_openEquipSkill, *_shopBtn;
		TMXTiledMap* _worldTileMap;
		std::vector<LocationInfoBtn*>* _locationBtns;
		std::vector<ChapterInfo*>* _chaptersInfo;
		ui::ScrollView* _worldView;
		ChapterInfo* _selectChapter;
		ChapterInfoRenderer* _chapterInfoRenderer;
		TTFConfig _font;
		CoinBar* _goldBar,* _rubyBar;
	private:
		bool loadProperties();
		bool loadComponent();
		bool loadCoins();
		void loadPosition();
		void onEnter() override;
	};
}

#endif // !__WORLD_MAP_H__
