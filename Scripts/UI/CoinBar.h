#ifndef __COIN_BAR_H__
#define __COIN_BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameReward/Coin.h"

USING_NS_CC;


namespace MyGame
{
	class CoinBar : public Node
	{
	public:
		static CoinBar* create(Coin* coin);
		void refresh();
		void setAmount(int amount);
		Sprite* getIcon() { return _iconCoin; }
	private:
		bool init(Coin* coin);
	private:
		CC_SYNTHESIZE(Size, _nodeSize, NodeSize);
		CC_SYNTHESIZE(Coin*, _coin, _Coin);
		Label* _coinAmount;
		ui::Button* _moreBtn;
		Sprite* _iconCoin;
	};
}

#endif // !__COIN_BAR_H__
