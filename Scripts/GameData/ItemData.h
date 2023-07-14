#ifndef __ITEM_DATA__
#define __ITEM_DATA__

#include "Inventory/Item/IItemInventory.h"
#include "GameData/SQLite/sqlite3.h"
#include "Projectile/Projectile.h"

using namespace MyGame;

namespace GameData
{
	class ItemData
	{
	public:
		IItemInventory* getItemByID(int id);
		IItemInventory* getItemByName(std::string name);
		std::vector<IItemInventory*> getItemsByType(ItemType type);
		Projectile* getProjectileByID(int id);

		static ItemQuality strToQuality(std::string qualityStr);
		static EquipableLocation strToEquipableLocation(std::string equipLocation);
	};
}

#endif // !__ITEM_DATA__
