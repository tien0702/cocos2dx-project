#include "WeaponData.h"
#include "SkillData.h"
#include "EntityData.h"
#include "Database.h"
#include "Convert.h"

std::vector<MagicBook*>* GameData::WeaponData::getWeapons()
{
	//Get connect
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	std::vector<MagicBook*>* weaps = new std::vector<MagicBook*>();

	std::string sqlCommand = "SELECT *" +
		std::string(" FROM ItemBase, Weapon") +
		std::string(" WHERE ItemBase.item_type_id = 1") +
		std::string(" AND ItemBase.reference_id = Weapon.id;");
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result != SQLITE_ROW) break;
			MagicBook* weap = this->getWeap(statement, 0);
			weaps->push_back(weap);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return weaps;
}

std::vector<MagicBook*>* GameData::WeaponData::getPlayerWeapons()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	std::vector<MagicBook*>* weaps = new std::vector<MagicBook*>();

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase, WeaponTemplate, Weapon" +
		std::string(" WHERE Weapon.weapon_template_id = WeaponTemplate.id AND ItemBase.name = WeaponTemplate.item_base_name;");
	sqlite3_stmt* statement;

	// 
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result != SQLITE_ROW) break;
			MagicBook* weap = this->getWeap(statement, 0);
			weaps->push_back(weap);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return weaps;
}

MagicBook* GameData::WeaponData::getWeaponByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	MagicBook* weap = nullptr;

	// create command query
	std::string sqlCommand = "SELECT *" +
		std::string(" FROM ItemBase, Weapon") +
		std::string(" WHERE ItemBase.id = ") +
		std::to_string(id) +
		std::string(" AND Weapon.id = reference_id;");
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			weap = this->getWeap(statement, 0);
			weap->setID(id);
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
	return weap;
}

MagicBook* GameData::WeaponData::getWeaponEquipped()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	MagicBook* weap = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase, WeaponTemplate, Weapon" +
		std::string(" Where Weapon.weapon_template_id = WeaponTemplate.id AND ItemBase.name = WeaponTemplate.item_base_name AND Weapon.equipped = 1;");
	sqlite3_stmt* statement;

	// 
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);

		if (result == SQLITE_ROW)
		{
			weap = this->getWeap(statement, 0);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return weap;
}

Power GameData::WeaponData::getPowerByID(int id, sqlite3* pdb)
{
	int result;
	// Value result
	Power power;

	std::string sqlCommand = "SELECT * FROM Power" +
		std::string(" WHERE id = ") + std::to_string(id) + " ;";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			power.setPowerValue(sqlite3_column_double(statement, 1));
			power.setPowerNumber(sqlite3_column_int(statement, 2));
			power.setElemType((ElementType)sqlite3_column_int(statement, 3));
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return power;
}

Power* GameData::WeaponData::getPowerByID(int id)
{
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);
	// Value result
	Power* power = nullptr;

	std::string sqlCommand = "SELECT * FROM Power" +
		std::string(" WHERE id = ") + std::to_string(id) + " ;";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			power = new Power();
			power->setPowerValue(sqlite3_column_double(statement, 1));
			power->setPowerNumber(sqlite3_column_int(statement, 2));
			power->setElemType(Convert::stringToElementType(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3))));
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return power;
}

MagicBook* GameData::WeaponData::getWeap(sqlite3_stmt* statement, int index)
{
	MagicBook* weap = new MagicBook();
	// Temporary variable
	std::string powerStr, statAllowedsStr;
	EntityData* entityData = new EntityData();
	SkillData* skillData = new SkillData();
	// Item Inventory
	weap->setType((ItemType)sqlite3_column_int(statement, ++index));
	weap->setItemEquipableLocation(ItemData::strToEquipableLocation(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
	weap->setQuality(ItemData::strToQuality(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
	weap->setItemName(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
	weap->setWeight(sqlite3_column_double(statement, ++index));
	weap->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
	std::string prices = reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index));
	weap->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));

	// Weapon (->12)
	index += 2;
	weap->setProjectileID(sqlite3_column_int(statement, ++index));
	weap->setSkillWeap(skillData->getPassiveSkillByID(sqlite3_column_int(statement, ++index)));
	weap->setStatBonus(entityData->getBonusByID(sqlite3_column_int(statement, ++index)));
	
	weap->setBnsATK(sqlite3_column_int(statement, ++index));
	weap->setRange(sqlite3_column_double(statement, ++index));
	weap->setWeapType((WeaponType)sqlite3_column_int(statement, ++index));
	statAllowedsStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index));
	weap->setID(sqlite3_column_int(statement, ++index));
	index += 1;
	weap->setLevel(sqlite3_column_int(statement, ++index));
	weap->setLocked((bool)sqlite3_column_int(statement, ++index));
	weap->setIsEquip((bool)sqlite3_column_int(statement, ++index));

	// Convert Tempoary variable to value Object
	std::string delimiter = ",";
	std::list<int> statAlloweds;
	size_t pos = 0;
	std::string token;
	while ((pos = statAllowedsStr.find(delimiter)) != std::string::npos) {
		token = statAllowedsStr.substr(0, pos);
		statAlloweds.push_back(std::atoi(token.c_str()));
		statAllowedsStr.erase(0, pos + delimiter.length());
	}
	statAlloweds.push_back(std::atoi(statAllowedsStr.c_str()));

	weap->setStateAlloweds(statAlloweds);
	return weap;
}
