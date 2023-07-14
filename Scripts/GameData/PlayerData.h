#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__

#include "ConsumableItem/ConsumableItem.h"
#include "GameReward/Coin.h"
#include "GameReward/Reward.h"
#include "Skill/Skill.h"

using namespace MyGame;

namespace GameData
{
	class PlayerData
	{
	public:
		static void addItem(ConsumableItem* item);
		static void addItems(std::list<ConsumableItem*> items);
		static void addCoin(Coin* coin);
		static void addCoins(std::map<CoinType, Coin*> coins);
		static void giveReward(Reward* reward);

		static bool canTakeCoin(int amount, CoinType coinType);
		static void takeCoin(int amount, CoinType coinType);

		static Coin* getCoin(CoinType type);

		void updateUltimate(std::string name);
		void updateTalen(std::string name);

		Skill* getUltimate();
		Skill* getTalen();
	};
}

#endif // !__PLAYER_DATA_H__
