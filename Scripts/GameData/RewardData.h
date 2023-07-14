#ifndef __REWARD_DATA_H__
#define __REWARD_DATA_H__

#include "GameReward/BonusDeck.h"
#include "GameReward/Reward.h"
#include "ObjectInfo/CoinInfo.h"
#include "ObjectInfo/ItemInfo.h"

using namespace MyGame;

namespace GameData
{
	class RewardData
	{
	public:
		Reward* getRewardByID(int id);
		std::map<CoinType, Coin*> getCoinsFromJson(std::string jsonData);
		std::list<ConsumableItem*> getItemsFromJson(std::string jsonData);
		Coin* getCoinByName(CoinInfo* info);
		BonusDeck* getBonusDeckByID(int id);
		void addCoin(Coin* coin);
		void addCoins(std::map<CoinType, Coin*> coins);
	};
}

#endif // !__REWARD_DATA_H__
