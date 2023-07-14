#ifndef __COINT_H__
#define __COINT_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	enum class CoinType
	{
		Coin_Gold,
		Coin_Ruby
	};

	class Coin : public Sprite
	{
	public:
		virtual bool init();

		void add(int amount);
		void remove(int amount);
	protected:
		CC_SYNTHESIZE(CoinType, _coinType, Coin_Type);
		CC_SYNTHESIZE(int, _amount, Amount);
		CC_SYNTHESIZE(std::string, _coinName, CoinName);
		CC_SYNTHESIZE(std::string, _iconPath, IconPath);
	};
}

#endif // !__COINT_H__
