#include "PlayerData.h"
#include "ItemData.h"
#include "ConsumableItemData.h"
#include "RewardData.h"
#include "SkillData.h"

void GameData::PlayerData::addItem(ConsumableItem* item)
{
	if (item == nullptr) return;
	ConsumableItemData data;
	data.addItem(item);
}

void GameData::PlayerData::addItems(std::list<ConsumableItem*> items)
{
	ConsumableItemData data;
	data.addItems(items);
}

void GameData::PlayerData::addCoin(Coin* coin)
{
	RewardData data;
	data.addCoin(coin);
}

void GameData::PlayerData::addCoins(std::map<CoinType, Coin*> coins)
{
	RewardData data;
	data.addCoins(coins);
}

void GameData::PlayerData::giveReward(Reward* reward)
{
	if (reward == nullptr)
	{
		log("Reward is null");
		return;
	}
	PlayerData::addCoins(reward->getCoins());
	PlayerData::addItems(reward->getItems());
}

bool GameData::PlayerData::canTakeCoin(int amount, CoinType coinType)
{
	auto coin = PlayerData::getCoin(coinType);
	return coin->getAmount() >= amount;
}

void GameData::PlayerData::takeCoin(int amount, CoinType coinType)
{
	auto coin = PlayerData::getCoin(coinType);
	if (coin->getAmount() < amount) return;

	// connect to db
	sqlite3* database = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &database);

	sqlite3_stmt* statement;
	char* sql = sqlite3_mprintf("UPDATE Coin SET quantity = quantity - %d WHERE id = %d;", amount, coinType);

	result = sqlite3_prepare_v2(database, sql, -1, &statement, NULL);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(database));
		sqlite3_close(database);
		return;
	}

	result = sqlite3_step(statement);
	if (result != SQLITE_DONE) {
		CCLOGERROR("Error executing SQL statement: %s", sqlite3_errmsg(database));
		sqlite3_finalize(statement);
		sqlite3_close(database);
		return;
	}

	// Finalize statement
	sqlite3_finalize(statement);
	sqlite3_close(database);
}

Coin* GameData::PlayerData::getCoin(CoinType type)
{

	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	std::string name = (type == CoinType::Coin_Gold) ? ("Gold") : ("Ruby");

	// create command query
	std::string sqlCommand = "select *from Coin where Coin.name = '" + name + "';";
	sqlite3_stmt* statement;
	Coin* coin = nullptr;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			coin = new Coin();
			int index = 0;
			coin->setCoin_Type(CoinType(sqlite3_column_int(statement, index++)));
			coin->setCoinName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			coin->setAmount(sqlite3_column_int(statement, index++));
			coin->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
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
	return coin;
}

void GameData::PlayerData::updateUltimate(std::string name)
{
	// connect to db
	sqlite3* db = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &db);

	// create query
	std::string sql = "UPDATE Player SET ultimate_name_equip = ?;";
	sqlite3_stmt* stmt;
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		CCLOG("Error preparing statement: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_bind_text(stmt, 1, name.c_str(), name.size(), SQLITE_TRANSIENT);
	// query
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		CCLOG("Error updating data: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	// close database
	result = sqlite3_finalize(stmt);
	result = sqlite3_close(db);
}

void GameData::PlayerData::updateTalen(std::string name)
{
	// connect to db
	sqlite3* db = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &db);

	// create query
	std::string sql = "UPDATE Player SET talen_name_equip = ?;";
	sqlite3_stmt* stmt;
	result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		CCLOG("Error preparing statement: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_bind_text(stmt, 1, name.c_str(), name.size(), SQLITE_TRANSIENT);
	// query
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		CCLOG("Error updating data: %s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	// close database
	result = sqlite3_finalize(stmt);
	result = sqlite3_close(db);
}

Skill* GameData::PlayerData::getUltimate()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// create command query
	std::string sqlCommand = "SELECT ultimate_name_equip FROM Player;";
	sqlite3_stmt* statement;
	Skill* skill = nullptr;

	std::string skillName = "";

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			skillName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
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

	//
	if (skillName != "")
	{
		auto skillDt = SkillData();
		skill = skillDt.getSkillByName(skillName);
	}
	return skill;
}

Skill* GameData::PlayerData::getTalen()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// create command query
	std::string sqlCommand = "SELECT talen_name_equip FROM Player;";
	sqlite3_stmt* statement;
	Skill* skill = nullptr;

	std::string skillName = "";

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			skillName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
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

	//
	if (skillName != "")
	{
		auto skillDt = SkillData();
		skill = skillDt.getSkillByName(skillName);
	}
	return skill;
}
