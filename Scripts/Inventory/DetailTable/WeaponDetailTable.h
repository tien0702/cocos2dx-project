#ifndef __WEAPON_DETAILE_TABLE_H__
#define __WEAPON_DETAILE_TABLE_H__

#include "Inventory/DetailTable/DetailTable.h"
#include "ui/CocosGUI.h"
#include "Equipment/Weapon/MagicBook.h"

namespace MyGame
{
	class WeaponDetailTable : public DetailTable
	{
	public:
		virtual bool init();
		virtual void showItem(SlotBox* slotBox);
		CREATE_FUNC(WeaponDetailTable);
	protected:
		ui::Button* _equipBT;
		ui::Button* _upgradeBT;
		MagicBook* _magicBook;

		SlotBox* _oldBox = nullptr;
		Label* _atkBns;
		Label* _statBns;

		void gotoUpgradeLayer();
	};
}

#endif // !__WEAPON_DETAILE_TABLE_H__
