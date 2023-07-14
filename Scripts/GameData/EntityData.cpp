#include "EntityData.h"
#include "Convert.h"

std::vector<std::string> splitString(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

std::vector<int> getNumberFromeStr(std::string str)
{
	// Convert Tempoary variable to value Object
	std::string delimiter = ",";
	std::vector<int> result;
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		result.push_back(std::atoi(token.c_str()));
		str.erase(0, pos + delimiter.length());
	}
	result.push_back(std::atoi(str.c_str()));

	return result;
}

GameData::EntityData::EntityData()
{
}

std::list<BaseStat*>* GameData::EntityData::getStats(sqlite3* pdb, int entityID)
{
	std::list<BaseStat*>* states = new std::list<BaseStat*>();
	std::string query = std::string("SELECT *") +
		std::string(" FROM EntityStat, Stat") +
		std::string(" INNER JOIN") +
		std::string(" BaseStat ON EntityStat.base_stat_id = BaseStat.id") +
		std::string(" WHERE entity_id = " + std::to_string(entityID) + " AND") +
		std::string(" BaseStat.stat_id = Stat.id;");

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pdb, query.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				int index = 3;
				BaseStat* baseStat = new BaseStat();
				Stat stat;

				baseStat->setBaseValue(sqlite3_column_int(statement, index++));
				baseStat->setGrowthValue(sqlite3_column_int(statement, index++));

				index = 6;
				stat.setID(sqlite3_column_int(statement, index++));
				stat.setType(StatType(sqlite3_column_int(statement, index++)));
				stat.setStatName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setAbbreviation(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setStatValueType(Convert::stringToValueType(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++))));
				stat.setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				baseStat->setEStat(stat);

				states->push_back(baseStat);
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return states;
}

std::list<BaseStat*>* GameData::EntityData::getStats(sqlite3* pdb, std::string entityName)
{
	std::list<BaseStat*>* states = new std::list<BaseStat*>();
	std::string query = std::string("SELECT *") +
		std::string(" FROM EntityStat, Stat") +
		std::string(" WHERE EntityStat.entity_name = \'") + entityName + std::string("\' AND ") +
		std::string(" EntityStat.stat_name = Stat.name;");

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pdb, query.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				int index = 3;
				BaseStat* baseStat = new BaseStat();
				Stat stat;

				baseStat->setBaseValue(sqlite3_column_int(statement, index++));
				baseStat->setGrowthValue(sqlite3_column_int(statement, index++));

				index = 5;
				stat.setID(sqlite3_column_int(statement, index++));
				stat.setType(StatType(sqlite3_column_int(statement, index++)));
				stat.setStatName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setAbbreviation(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setStatValueType(Convert::stringToValueType(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++))));
				stat.setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				baseStat->setEStat(stat);

				states->push_back(baseStat);
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return states;
}

Character* GameData::EntityData::getCharacter()
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
	Character* character = new Character();

	// create command query
	std::string sqlCommand = "SELECT * FROM Entity WHERE id = 1;";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			character->setID(sqlite3_column_int(statement, index++));
			character->setType((EntityType)sqlite3_column_int(statement, index++));
			character->setEntityName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			character->setExp(sqlite3_column_int(statement, index++));
			character->setWeight(sqlite3_column_int(statement, index++));
			character->setPortraitFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			character->setSpriteFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));

			std::list<BaseStat*>* stats = this->getStats(pdb, character->getEntityName());
			character->setStats(stats);

			std::string sizeInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<int> sizeVal = getNumberFromeStr(sizeInfo);
			Size size;
			size.width = sizeVal.at(0);
			size.height = sizeVal.at(1);
			character->setEntitySize(size);

			std::string statesInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<std::string> states = splitString(statesInfo, ',');
			character->setStates(states);
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
	character->setLevel(50);
	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return character;
}

Enemy* GameData::EntityData::getEnemyByID(int id)
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
	Enemy* enemy = new Enemy();

	// create command query
	std::string sqlCommand = "SELECT * FROM Entity WHERE id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			enemy->setID(sqlite3_column_int(statement, index++));
			enemy->setType((EntityType)sqlite3_column_int(statement, index++));
			enemy->setEntityName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setExp(sqlite3_column_int(statement, index++));
			enemy->setWeight(sqlite3_column_int(statement, index++));
			enemy->setPortraitFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setSpriteFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setStats(this->getStats(pdb, enemy->getEntityName()));

			std::string sizeInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<int> sizeVal = getNumberFromeStr(sizeInfo);
			Size size;
			size.width = sizeVal.at(0);
			size.height = sizeVal.at(1);
			enemy->setEntitySize(size);

			std::string statesInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<std::string> states = splitString(statesInfo, ',');
			enemy->setStates(states);
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
	return enemy;
}

Enemy* GameData::EntityData::getEnemyByName(std::string name)
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
	Enemy* enemy = new Enemy();

	// create command query
	std::string sqlCommand = "SELECT * FROM Entity WHERE Entity.name = '" + name + "';";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			enemy->setID(sqlite3_column_int(statement, index++));
			enemy->setType((EntityType)sqlite3_column_int(statement, index++));
			enemy->setEntityName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setExp(sqlite3_column_int(statement, index++));
			enemy->setWeight(sqlite3_column_int(statement, index++));
			enemy->setPortraitFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setSpriteFileName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			enemy->setStats(this->getStats(pdb, enemy->getEntityName()));

			std::string sizeInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<int> sizeVal = getNumberFromeStr(sizeInfo);
			Size size;
			size.width = sizeVal.at(0);
			size.height = sizeVal.at(1);
			enemy->setEntitySize(size);

			std::string statesInfo = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			std::vector<std::string> states = splitString(statesInfo, ',');
			enemy->setStates(states);
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
	return enemy;
}

Bonus* GameData::EntityData::getBonusByID(int id)
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
	Bonus* bonus = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM Bonus WHERE id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			bonus = new Bonus();
			bonus->setBnsID(sqlite3_column_int(statement, index++));
			Stat stat = this->getStatByName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			bonus->setStatBns(stat);
			std::string val = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			if (val == "Percentage") bonus->setStatModifiType(StatModificationType::Percentage);
			else if (val == "Numeric") bonus->setStatModifiType(StatModificationType::Numeric);
			else if (val == "Absolute") bonus->setStatModifiType(StatModificationType::Absolute);
			else if (val == "BaseValue") bonus->setStatModifiType(StatModificationType::BaseValue);

			bonus->setStatusEff((StatusEffect)sqlite3_column_int(statement, index++));
			bonus->setDuration(sqlite3_column_int(statement, index++));
			bonus->setTimeStarted(sqlite3_column_int(statement, index++));
			bonus->setValueBns(sqlite3_column_int(statement, index++));
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

	return bonus;
}

BaseStat* GameData::EntityData::getBaseStatByID(int id)
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
	BaseStat* baseStat = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM ObjectStat WHERE id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			baseStat = new BaseStat();
			Stat st = this->getStatByName(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
			baseStat->setEStat(st);
			baseStat->setBaseValue(sqlite3_column_int(statement, 2));
			std::string type = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
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
	return baseStat;
}

Stat GameData::EntityData::getStatByID(int id)
{
	// Open database

	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	Stat resultStat;

	// create command query
	std::string sqlCommand = "SELECT * FROM Stat WHERE Stat.id = " + std::to_string(id) + " ;";
	sqlite3_stmt* statement;

	// 

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			resultStat.setID(id);
			resultStat.setType((StatType)sqlite3_column_int(statement, ++index));
			resultStat.setStatName(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
			resultStat.setAbbreviation(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
			resultStat.setStatValueType(Convert::stringToValueType(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
			resultStat.setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
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
	return resultStat;
}

Stat GameData::EntityData::getStatByName(std::string name)
{
	// Open database

	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	Stat resultStat;

	// create command query
	std::string sqlCommand = "SELECT * FROM Stat WHERE Stat.name = '" + name + "';";
	sqlite3_stmt* statement;

	// query
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			resultStat.setID(sqlite3_column_int(statement, index));
			resultStat.setType((StatType)sqlite3_column_int(statement, ++index));
			resultStat.setStatName(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
			resultStat.setAbbreviation(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
			resultStat.setStatValueType(Convert::stringToValueType(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index))));
			resultStat.setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, ++index)));
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
	return resultStat;
}
