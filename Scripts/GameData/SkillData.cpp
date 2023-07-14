#include "SkillData.h"
#include "GameData/Database.h"
#include "Entity/BaseStat.h"
#include "Skill/TargetingStrategy/TargetingFactory.h"
#include "Skill/ActivationStrategy/ActivationFactory.h"
#include "EntityData.h"
#include "WeaponData.h"
#include "Convert.h"


PassiveSkill* GameData::SkillData::getPassiveSkillByID(int id)
{
	PassiveSkill* skill = new PassiveSkill();
	skill->setLevel(1);
	skill->setName("");
	skill->setDescription("");
	skill->setCooldown(1.0f);
	skill->setCondition(std::pair<int, std::string>(1, ""));

	skill->setSuccessRate(0.9f);

	return skill;
}

Skill* GameData::SkillData::getSkillByID(int id)
{
	return nullptr;
}

Skill* GameData::SkillData::getSkillByName(std::string name)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	Skill* skill = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM SkillTemplate WHERE SkillTemplate.name = '" + name + "';";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 0;
			skill = new Skill();

			// Skill Info
			SkillInfo* info = new SkillInfo();
			info->setSkillID(sqlite3_column_int(statement, index++));
			info->setSkillName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			info->setDescription(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			info->setIconName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			info->setEffectName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			skill->setInfo(info);

			skill->setActivationButtonID((InputID)sqlite3_column_int(statement, index++));
			SkillTargeting* targeting = TargetingFactory::getTargetingByType((TargetingType)sqlite3_column_int(statement, index++));
			skill->setTargeting(targeting);
			SkillActivation* activation = ActivationFactory::getActivationByType((ActivationType)sqlite3_column_int(statement, index++));
			skill->setActivation(activation);

			// power
			int powerId = sqlite3_column_int(statement, index++);
			auto wData = WeaponData();
			Power* power = wData.getPowerByID(powerId);
			skill->setSkillPower(power);

			// Skill Stats
			skill->setStats(getStatsBySkillName(name));
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
	return skill;
}

std::vector<Skill*>* GameData::SkillData::getPlayerSkills()
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	auto skills = new std::vector<Skill*>();

	std::string sqlCommand = "SELECT skill_template_name FROM Skill;";

	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		while (true)
		{
			result = 0;
			result = sqlite3_step(statement);
			if (result != SQLITE_ROW) break;
			std::string name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
			auto skill = getSkillByName(name);
			if (skill == nullptr)
			{
				log("get skill failed!");
			}
			else
			{
				skills->push_back(skill);
			}
		}
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return skills;
}

std::vector<Skill*>* GameData::SkillData::getSkills()
{
	return nullptr;
}

std::map<int, BaseStat*> GameData::SkillData::getStatsBySkillName(std::string skillName)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// 
	map<int, BaseStat*> stats;

	// create command query
	std::string sqlCommand = "SELECT * FROM SkillStat WHERE SkillStat.skill_name = '" + skillName + "';";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int result = 0;
		while (true)
		{
			EntityData entityData;
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				BaseStat* baseStat = new BaseStat();
				baseStat->setBaseValue(sqlite3_column_int(statement, 3));

				std::string statName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
				Stat stat = entityData.getStatByName(statName);
				baseStat->setEStat(stat);

				baseStat->setOwner(nullptr);

				auto statVal = std::pair<int, BaseStat*>(baseStat->getEStat().getID(), baseStat);
				stats.insert(statVal);
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
	return stats;
}
