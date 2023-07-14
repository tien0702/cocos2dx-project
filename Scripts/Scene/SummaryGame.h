#ifndef __SUMMARY_GAME_H__
#define __SUMMARY_GAME_H__

#include "cocos2d.h"
#include "Chapter/Chapter.h"
#include "ConsumableItem/ConsumableItem.h"
#include "WorldMap.h"
#include "HomeScene.h"

USING_NS_CC;

using namespace std;

namespace MyGame
{
	class SummaryGame : public Scene
	{
	public:
		virtual bool init();

		CREATE_FUNC(SummaryGame);
		virtual void rewardRender();
	protected: // component
		Label* _gameStateLb;
	protected:// properties
		Chapter* _chapter;
		TTFConfig _font;
		int _exp;
		vector<Coin*> _coins;
		vector<ConsumableItem*> _items;
	protected:
		virtual bool loadProperties();
		virtual bool loadComponent();

		virtual void showCoins();
		virtual void showItems();
		virtual void showExp();

		virtual void gotoWorldMap();

	};
}

#endif // !__SUMMARY_GAME_H__
