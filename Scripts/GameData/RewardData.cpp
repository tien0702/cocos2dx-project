#include "RewardData.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "ItemData.h"
#include "EntityData.h"
#include "ConsumableItemData.h"

using namespace rapidjson;

std::vector<int> splitStringToIntVector(const std::string& inputStr, const char delimiter = ',') {
	std::vector<int> outputVector;
	std::stringstream ss(inputStr);
	std::string token;

	while (getline(ss, token, delimiter)) {
		outputVector.push_back(std::stoi(token));
	}

	return outputVector;
}

MyGame::Reward* GameData::RewardData::getRewardByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);
	Reward* reward = nullptr;

	// create command query
	std::string sqlCommand = "SELECT *FROM Reward WHERE Reward.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			reward = new Reward();
			std::string coinJsonData, itemJsonData;

			int index = 1;
			reward->setID(id);
			reward->setExpReward(sqlite3_column_int(statement, index++));
			coinJsonData = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			itemJsonData = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::map<CoinType, Coin*> coins = this->getCoinsFromJson(coinJsonData);
			std::list<ConsumableItem*> items = this->getItemsFromJson(itemJsonData);

			reward->setCoins(coins);
			reward->setItems(items);
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
	return reward;
}

std::map<CoinType, Coin*> GameData::RewardData::getCoinsFromJson(std::string jsonData)
{
	std::map<CoinType, Coin*> coins;
	Document docs;

	docs.Parse<0>(jsonData.c_str());
	if (docs.HasParseError()) {
		log("Has error!");
	}

	if (!docs.IsArray()) {
		log("Error: Input JSON is not an array.");
	}
	else 
	{

		CoinInfo* info = new CoinInfo();
		for (rapidjson::SizeType i = 0; i < docs.Size(); i++)
		{
			std::string name = docs[i]["Name"].GetString();
			int amount = docs[i]["Amount"].GetInt();
			info->setCoinName(name);
			Coin* coin = this->getCoinByName(info);
			coin->setAmount(amount);
			coins.insert(std::pair<CoinType, Coin*>(coin->getCoin_Type(), coin));
		}
	}

	return coins;
}

std::list<ConsumableItem*> GameData::RewardData::getItemsFromJson(std::string jsonData)
{
	std::list<ConsumableItem*> items;

	ConsumableItemData data;

	Document docs;
	docs.Parse<0>(jsonData.c_str());
	if (docs.HasParseError()) {
		log("Has error!");
	}

	if (!docs.IsArray()) {
		log("Error: Input JSON is not an array.");
	}
	else
	{
		for (rapidjson::SizeType i = 0; i < docs.Size(); i++)
		{
			std::string name = docs[i]["Name"].GetString();
			int amount = docs[i]["Amount"].GetInt();
			ConsumableItem* item = data.getByName(name);
			if (item != nullptr)
			{
				item->setQuantity(amount);
				items.push_back(item);
			}
		}
	}
	return items;
}

Coin* GameData::RewardData::getCoinByName(CoinInfo* info)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// create command query
	std::string sqlCommand = "select *from Coin where Coin.name = '" + info->getCoinName() + "';";
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

BonusDeck* GameData::RewardData::getBonusDeckByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	BonusDeck* deck = nullptr;

	// create command query
	std::string sqlCommand = "select *from BonusDeck where BonusDeck.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			deck = new BonusDeck();
			std::string bonusesInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			std::vector<int> bonusIDList = splitStringToIntVector(bonusesInfo, ',');
			if (bonusIDList.empty())
			{
				sqlite3_close(pdb);
				return nullptr;
			}
			EntityData* entityData = new EntityData();
			int index = 1;
			for (int i = 0; i < bonusIDList.size(); ++i)
			{
				Bonus* bonus = entityData->getBonusByID(bonusIDList.at(i));
				if (bonus == nullptr) continue;
				deck->addBonus("Card" + std::to_string(index++), bonus);
			}
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
	return deck;
}

void GameData::RewardData::addCoin(Coin* coin)
{
	// connect to db
	sqlite3* database = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &database);

	sqlite3_stmt* statement;
	char* sql = sqlite3_mprintf("UPDATE Coin SET quantity = quantity + %d WHERE id = %d;", coin->getAmount(), (int)coin->getCoin_Type());

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

void GameData::RewardData::addCoins(std::map<CoinType, Coin*> coins)
{
	for (auto coin : coins)
	{
		this->addCoin(coin.second);
	}
}
