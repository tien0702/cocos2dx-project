#ifndef __WEAPON_DATA_H__
#define __WEAPON_DATA_H__

#include "GameData/ItemData.h"
#include "Equipment/Weapon/MagicBook.h"
#include "Projectile/Projectile.h"

using namespace MyGame;

namespace GameData
{
	class WeaponData
	{
	public:
		std::vector<MagicBook*>* getWeapons();
		std::vector<MagicBook*>* getPlayerWeapons();
		MagicBook* getWeaponByID(int id);
		MagicBook* getWeaponEquipped();
		Power getPowerByID(int id, sqlite3* pdb);
		Power* getPowerByID(int id);
	private:
		MagicBook* getWeap(sqlite3_stmt* statement, int index);
	};
}

#endif // !__WEAPON_DATA_H__
