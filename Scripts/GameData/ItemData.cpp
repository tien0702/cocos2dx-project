#include "ItemData.h"
#include "Common.h"
#include "GameData/Database.h"

IItemInventory* GameData::ItemData::getItemByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	IItemInventory* item = new IItemInventory();

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase WHERE id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			item->setID(id);
			item->setType((ItemType)sqlite3_column_int(statement, 1));
			item->setItemEquipableLocation(EquipableLocation(sqlite3_column_int(statement, 3)));
			item->setQuality((ItemQuality)sqlite3_column_int(statement, 4));
			item->setItemName(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7)));
			item->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, 9)));
			item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, 8)));
			std::string values = reinterpret_cast<const char*>(sqlite3_column_text(statement, 6));
			item->setPrice(Common::splitNumbers(values).at(0));

			item->setWeight(sqlite3_column_double(statement, 5));
		}
		else
		{
			log("SQLite query failed!");
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	item->setIconPath("Icon/skill_00008.png");
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return item;
}

IItemInventory* GameData::ItemData::getItemByName(std::string name)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	IItemInventory* item = new IItemInventory();

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase WHERE ItemBase.name = '" + name + "';";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			item->setID(sqlite3_column_int(statement, index++));
			item->setType((ItemType)sqlite3_column_int(statement, index++));
			item->setItemEquipableLocation(this->strToEquipableLocation(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++))));
			item->setQuality(this->strToQuality(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++))));
			item->setItemName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			item->setWeight(sqlite3_column_int(statement, index++));
			item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			std::string values = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			item->setPrice(Common::splitNumbers(values).at(0));
			item->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
		}
		else
		{
			log("SQLite query failed!");
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return item;
}

std::vector<IItemInventory*> GameData::ItemData::getItemsByType(ItemType type)
{
	return std::vector<IItemInventory*>();
}

Projectile* GameData::ItemData::getProjectileByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	if (result != SQLITE_OK) {
		log("Open Database failed!");
		sqlite3_close(pdb);
		return nullptr;
	}
	// Value result
	Projectile* projectile = new Projectile();

	// create command query
	std::string sqlCommand = "SELECT * FROM Projectile WHERE id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			projectile->setIDType(id);
			projectile->setRange(sqlite3_column_double(statement, 1));
			projectile->setProjectileSpeed(sqlite3_column_double(statement, 2));
			projectile->setProjectilePath(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
			projectile->setAnimationPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4)));
			projectile->setProjectileRadius(sqlite3_column_double(statement, 5));
		}
		else
		{
			log("SQLite query failed!");
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return projectile;
}

ItemQuality GameData::ItemData::strToQuality(std::string qualityStr)
{
	if (qualityStr == "Normal") return ItemQuality::NormalItem;
	if (qualityStr == "Rare") return ItemQuality::RareItem;
	if (qualityStr == "Legendary") return ItemQuality::LegendaryItem;
	return ItemQuality::NormalItem;
}

EquipableLocation GameData::ItemData::strToEquipableLocation(std::string equipLocation)
{

	if (equipLocation == "Weapon") return EquipableLocation::WeaponLocation;
	if (equipLocation == "RuneTop") return EquipableLocation::RuneTopLocation;
	if (equipLocation == "RuneMiddle") return EquipableLocation::RuneMiddleLocation;
	if (equipLocation == "RuneBottom") return EquipableLocation::RuneBottomLocation;

	return EquipableLocation::Non;
}
