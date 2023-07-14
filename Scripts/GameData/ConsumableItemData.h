#ifndef __CONSUMABLE_ITEM_DATA_H__
#define __CONSUMABLE_ITEM_DATA_H__

#include "ConsumableItem/ConsumableItem.h"
#include "GameData/ItemData.h"

using namespace MyGame;

namespace GameData
{
	class ConsumableItemData
	{
	public:
		std::vector<ConsumableItem*> getConsumableItems();
		std::vector<ConsumableItem*>* getPlayerConsumableItems();
		ConsumableItem* getByID(int id);
		ConsumableItem* getByName(std::string name);
		ConsumableItem* getConsumableItem(sqlite3_stmt* statement, int index);

		void addItem(ConsumableItem* item);
		void addItems(std::list<ConsumableItem*> items);
		bool useItem(ConsumableItem* item);
		bool updateConsumableItem(ConsumableItem* item);
	};
}

#endif // !__CONSUMABLE_ITEM_DATA_H__
