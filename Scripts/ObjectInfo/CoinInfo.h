#ifndef __COINT_INFO_H__
#define __COINT_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	class CoinInfo
	{
	protected:
		CC_SYNTHESIZE(int, _coinID, CoinID);
		CC_SYNTHESIZE(int, _amount, Amount);
		CC_SYNTHESIZE(std::string, _coinName, CoinName);
	};
}

#endif // !__COINT_INFO_H__
