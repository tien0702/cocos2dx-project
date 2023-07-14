#ifndef __SLOT_BOX_EQUIPMENT_H__
#define __SLOT_BOX_EQUIPMENT_H__


#include "Inventory/SlotBox/SlotBox.h"
#include "Equipment/Weapon/MagicBook.h"
namespace MyGame
{
	class SlotBoxEquipment : public SlotBox
	{
	public:
		virtual bool init();
		SlotBoxEquipment(IItemInventory* item);
	private:
		virtual bool loadProperties();
		Sprite* _equippedSprite;
		std::string _equippedPath;
		MagicBook* _magicBook;
	};
}

#endif // !__SLOT_BOX_EQUIPMENT_H__
