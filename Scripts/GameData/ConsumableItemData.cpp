#include "GameData/ConsumableItemData.h"
#include "Database.h"
#include "GameData/EntityData.h"
#include "GameData/ItemData.h"
#include "Common.h"

std::vector<ConsumableItem*> GameData::ConsumableItemData::getConsumableItems()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	std::vector<ConsumableItem*> items;

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase, ConsumableItemTemplate, ConsumableItem" +
		std::string(" WHERE ConsumableItem.consumable_item_template = ConsumableItemTemplate.id AND ItemBase.name = ConsumableItemTemplate.item_base_name;");
	sqlite3_stmt* statement;

	// query
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result != SQLITE_ROW) break;
			ConsumableItem* item = this->getConsumableItem(statement, 0);
			item->setType(ItemType::ComsumableType);
			items.push_back(item);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);

	return items;
}

std::vector<ConsumableItem*>* GameData::ConsumableItemData::getPlayerConsumableItems()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	std::vector<ConsumableItem*>* items = new std::vector<ConsumableItem*>();

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase, ConsumableItemTemplate, ConsumableItem" +
		std::string(" WHERE ConsumableItem.consumable_item_template = ConsumableItemTemplate.id AND ItemBase.name = ConsumableItemTemplate.item_base_name;");
	sqlite3_stmt* statement;

	// 
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result != SQLITE_ROW) break;
			ConsumableItem* item = this->getConsumableItem(statement, 0);
			item->setType(ItemType::ComsumableType);
			items->push_back(item);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return items;
}

ConsumableItem* GameData::ConsumableItemData::getByID(int id)
{
	return nullptr;
}

ConsumableItem* GameData::ConsumableItemData::getByName(std::string name)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	ConsumableItem* item = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM ItemBase, ConsumableItemTemplate" +
		std::string(" WHERE ConsumableItemTemplate.item_base_name = '" + name + "' AND ") +
		std::string("ConsumableItemTemplate.item_base_name = ItemBase.name;");
	sqlite3_stmt* statement;

	// 
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = sqlite3_step(statement);
		item = getConsumableItem(statement, 0);
	}
	else
	{
		log("SQLite prepare failed!");
	}
	sqlite3_finalize(statement);
	sqlite3_close(pdb);

	return item;
}

ConsumableItem* GameData::ConsumableItemData::getConsumableItem(sqlite3_stmt* statement, int index)
{
	ConsumableItem* item = new ConsumableItem();
	EntityData data;

	// Item base
	item->setType((ItemType)sqlite3_column_int(statement, ++index));
	item->setItemEquipableLocation(ItemData::strToEquipableLocation(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
	item->setQuality(ItemData::strToQuality(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
	item->setItemName(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
	item->setWeight(sqlite3_column_double(statement, ++index));
	item->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
	std::string prices = reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index));
	item->setPrice(Common::splitNumbers(prices).at(0));
	item->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));

	// Consumable Item
	index += 2;
	item->setItemBonus(data.getBonusByID(sqlite3_column_int(statement, ++index)));
	std::string consumItemType = reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index));
	item->setID(sqlite3_column_int(statement, ++index));

	index += 1;
	item->setQuantity(sqlite3_column_int(statement, ++index));
	return item;
}

void GameData::ConsumableItemData::addItem(ConsumableItem* item)
{
	if (item == nullptr)
	{
		log("item is nullptr");
		return;
	}

	// connect to db
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);
	if (pdb == nullptr) {
		log("Error opening database: %s", sqlite3_errmsg(pdb));
		sqlite3_close(pdb);
		return;
	}

	sqlite3_stmt* statement;
	char* sql = "UPDATE ConsumableItem SET quantity = quantity + ? WHERE consumable_item_template = ?;";

	// Prepare SQL statement
	if (sqlite3_prepare_v2(pdb, sql, -1, &statement, nullptr) != SQLITE_OK) {
		CCLOGERROR("Error preparing SQL statement: %s", sqlite3_errmsg(pdb));
		sqlite3_finalize(statement);
		sqlite3_close(pdb);
		return;
	}

	// Bind parameters
	sqlite3_bind_int(statement, 1, item->getQuantity());
	sqlite3_bind_int(statement, 2, item->getID());

	// Execute statement
	if (sqlite3_step(statement) != SQLITE_DONE) {
		CCLOGERROR("Error executing SQL statement: %s", sqlite3_errmsg(pdb));
		sqlite3_finalize(statement);
		sqlite3_close(pdb);
		return;
	}

	// Finalize statement
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
}

void GameData::ConsumableItemData::addItems(std::list<ConsumableItem*> items)
{
	if (items.empty())
	{
		log("list items is nullptr");
		return;
	}

	for (auto item : items)
	{
		addItem(item);
	}
}

bool GameData::ConsumableItemData::useItem(ConsumableItem* item)
{
	// connect to db
	sqlite3* db = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &db);

	// calculate quantity, getid
	int newQuantity = item->getQuantity() - 1; // newQuantity
	int itemId = item->getID(); // id item

	// create query
	std::string sql = "UPDATE ConsumableItem SET quantity = ? WHERE id = ?;";
	sqlite3_stmt* stmt;
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		CCLOG("Error preparing statement: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}

	// update quantity
	result = sqlite3_bind_int(stmt, 1, newQuantity);
	result = sqlite3_bind_int(stmt, 2, itemId);

	// query
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		CCLOG("Error updating data: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		item->setQuantity(newQuantity);
		return true;
	}

	// close database
	result = sqlite3_finalize(stmt);
	result = sqlite3_close(db);
	item->setQuantity(newQuantity);

	return true;
}

bool GameData::ConsumableItemData::updateConsumableItem(ConsumableItem* item)
{
	// connect to db

	sqlite3* database = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &database);

	sqlite3_stmt* statement;
	char* sql = "UPDATE ConsumableItem SET quantity = quantity + ? WHERE consumable_item_template = ?;";

	// Prepare SQL statement
	if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
		CCLOGERROR("Error preparing SQL statement: %s", sqlite3_errmsg(database));
		sqlite3_finalize(statement);
		sqlite3_close(database);
		return false;
	}

	// Bind parameters
	sqlite3_bind_int(statement, 1, item->getQuantity());
	sqlite3_bind_int(statement, 2, item->getID());

	// Execute statement
	if (sqlite3_step(statement) != SQLITE_DONE) {
		CCLOGERROR("Error executing SQL statement: %s", sqlite3_errmsg(database));
		sqlite3_finalize(statement);
		sqlite3_close(database);
		return false;
	}

	result = sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		CCLOGERROR("Error executing SQL statement: %s", sqlite3_errmsg(database));
		sqlite3_finalize(statement);
		sqlite3_close(database);
		return false;
	}

	// Finalize statement
	sqlite3_finalize(statement);
	sqlite3_close(database);
	return true;
}
