#include "AbilityData.h"
#include "Entity/BaseStat.h"

ActiveSkillLocation strToAbilityLocation(std::string str)
{
	ActiveSkillLocation result = ActiveSkillLocation::Non;
	if (str == "DashLocation") result = ActiveSkillLocation::DashSkill;
	else if (str == "TalenLocation") result = ActiveSkillLocation::DashSkill;
	else if (str == "UltimateLocation") result = ActiveSkillLocation::DashSkill;

	return result;
}

std::map<int, BaseStat*>* GameData::AbilityData::getStats(sqlite3* pdb, std::string abilityName)
{
	std::map<int, BaseStat*>* states = new std::map<int, BaseStat*>();
	std::string query = std::string("SELECT *") +
		std::string(" FROM AbilityStat, Stat") +
		std::string(" WHERE AbilityStat.ability_name = \'") + abilityName + std::string("\' AND ") +
		std::string(" AbilityStat.stat_name = Stat.name;");

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

				stat.setID(sqlite3_column_int(statement, index++));
				stat.setType(StatType(sqlite3_column_int(statement, index++)));
				stat.setStatName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setAbbreviation(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				stat.setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
				baseStat->setEStat(stat);
				baseStat->setOwner(nullptr);

				auto val = std::pair<int, BaseStat*>(stat.getID(), baseStat);
				states->insert(val);
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

ActiveSkill* GameData::AbilityData::getAbilityByID(int id)
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
	ActiveSkill* ability = new ActiveSkill();

	// create command query
	std::string sqlCommand = "SELECT * FROM Ability WHERE Ability.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			ability->setID(sqlite3_column_int(statement, index++));
			ability->setLevel(sqlite3_column_int(statement, index++));
			ability->setUnlockLevel(sqlite3_column_int(statement, index++));
			std::string locationStr = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			ability->setEquipLocation(strToAbilityLocation(locationStr));
			index++;
			ability->setAbilityName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			ability->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			ability->setIconPath(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			ability->setStats(this->getStats(pdb, ability->getAbilityName()));
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
	return ability;
}
