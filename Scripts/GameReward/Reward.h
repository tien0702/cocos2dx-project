#ifndef __REWARD_H__
#define __REWARD_H__

#include "GameReward/Coin.h"
#include "Inventory/Item/IItemInventory.h"
#include "Character/Character.h"
#include "GameData/Database.h"
#include "ConsumableItem/ConsumableItem.h"

namespace MyGame
{
	class Reward
	{
	public:
		void add(Reward* reward);
		void addCoin(Coin* coin);
		void addCoins(std::map<CoinType, Coin*> coins);
		void removeCoin(Coin* coin);

		void addItem(ConsumableItem* item);
		void addItems(std::list<ConsumableItem*> items);
		void removeItem(ConsumableItem* item);

		void addExp(int amount);
		void removeExp(int amount);

		void setItems(std::list<ConsumableItem*> items);
		void setCoins(std::map<CoinType, Coin*> coins);

		void giveReward();

		std::list<ConsumableItem*> getItems() { return _items; }
		std::map<CoinType, Coin*> getCoins() { return this->_coins; }
	private:
		int getNextLevelExp();
	private:
		CC_SYNTHESIZE(int, _id, ID);
		CC_SYNTHESIZE(int, _expReward, ExpReward);
		CC_SYNTHESIZE(Character*, _character, TargetCharacter);

		std::list<ConsumableItem*> _items;
		std::map<CoinType, Coin*> _coins;
	};
}

#endif // !__REWARD_H__
