#ifndef __PLAYER_INVENTORY_H__
#define __PLAYER_INVENTORY_H__

#include "Inventory/Item/IItemInventory.h"
#include "Inventory/InventoryBase.h"
#include "ConsumableItem/ConsumableItem.h"
#include "Equipment/Weapon/MagicBook.h"
#include "Character/Character.h"

namespace MyGame
{
	class PlayerInventory
	{
	public:
		static PlayerInventory* getIns();
		std::string equipItem(IItemInventory* item);
		std::string unequip(EquipableLocation location);
		std::string useItem(ConsumableItem* item);

		void addItem(IItemInventory* item);
		void removeItem(IItemInventory* item);
	private:
		static PlayerInventory* _instance;
		PlayerInventory();
		Character* _character;

		std::map<EquipableLocation, IItemInventory*>* _equipped;
		std::map<ItemType, InventoryBase*>* _ivns;

		std::string equipWeapon(MagicBook* weap);
		std::string unequipWeapon();
	};
}

#endif // !__PLAYER_INVENTORY_H__
