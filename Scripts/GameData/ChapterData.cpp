#include "ChapterData.h"
#include "Chapter/EnemyWave.h"
#include "Chapter/Chapter.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "GameData/EntityData.h"
#include "RewardData.h"

using namespace rapidjson;

MyGame::Chapter* GameData::ChapterData::getChapterByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	Chapter* _chapter = new Chapter();

	// create command query
	std::string sqlCommand = "SELECT * FROM Chapter WHERE Chapter.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 1;
			_chapter->setIDChapter(id);
			std::string chapterName = reinterpret_cast<const char*>(sqlite3_column_text(statement, index++));
			_chapter->setChapterName(chapterName);

			RewardData* rewarData = new RewardData();
			int rewardID = sqlite3_column_int(statement, index++);
			Reward* reward = rewarData->getRewardByID(rewardID);
			_chapter->setChapterReward(reward);
			_chapter->setMapIDs(this->getChapterMapsByChapterName(pdb, chapterName));
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
	return _chapter;
}

ChapterInfo* GameData::ChapterData::getChapterInfoByID(int id)
{
	// Open database

	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// create command query
	std::string sqlCommand = "select *from Chapter where Chapter.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;

	// variable result
	ChapterInfo* info = nullptr;


	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 1;
			info = new ChapterInfo();
			info->setChapterID(id);

			info->setChapterName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			info->setRewardID(sqlite3_column_int(statement, index++));
			info->setState((ChapterState)sqlite3_column_int(statement, index++));

			auto maps = getChapterMapsByChapterName(pdb, info->getChapterName());
			info->setMapIDs(maps);
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return info;
}

std::vector<int> GameData::ChapterData::getChapterMapsByChapterName(sqlite3* pdb, std::string chapterName)
{
	// create command query
	std::string sqlCommand = "SELECT id FROM ChapterMap WHERE ChapterMap.chapter_name = '" + chapterName + "';";
	sqlite3_stmt* statement;

	int result = 0;
	std::vector<int> maps;

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				int id = sqlite3_column_int(statement, 0);
				this->getEnemyWaveInChapterMap(id);
				maps.push_back(id);
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
	return maps;
}

std::vector<EnemyWave*> GameData::ChapterData::getEnemyWaveInChapterMap(int chapterMapID)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// create command query
	std::string sqlCommand = "SELECT enemy_wave_json FROM ChapterMap WHERE ChapterMap.id = " + std::to_string(chapterMapID) + ";";
	sqlite3_stmt* statement;
	std::vector<EnemyWave*> waves;
	EntityData* entityData = new EntityData();

	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			std::string jsonVal = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
			Document docs;

			docs.Parse<0>(jsonVal.c_str());
			if (docs.HasParseError()) {
				log("Has error!");
			}
			else
			{
				vector<pair<string, int>> infoEnemies;
				for (int i = 0; i < docs.Size(); ++i)
				{
					EnemyWave* wave = new EnemyWave();
					for (rapidjson::SizeType j = 0; j < docs[i]["Enemies"].Size(); ++j)
					{
						std::string name = docs[i]["Enemies"][j]["EnemyName"].GetString();
						int level = docs[i]["Enemies"][j]["Level"].GetInt();
						pair<string, int> info = pair<string, int>();
						info.first = name;
						info.second = level;
						infoEnemies.push_back(info);
					}
					wave->setInfoEnemies(infoEnemies);
					waves.push_back(wave);
				}
			}
		}
	}
	else
	{
		log("SQLite prepare failed!");
	}

	sqlite3_finalize(statement);
	sqlite3_close(pdb);
	return waves;
}

ChapterMapInfo* GameData::ChapterData::getChapterMapInfoByID(int id)
{
	// Open database
	sqlite3* pdb = nullptr;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	// Value result
	ChapterMapInfo* chapterMapInfo = nullptr;

	// create command query
	std::string sqlCommand = "SELECT * FROM ChapterMap WHERE ChapterMap.id = " + std::to_string(id) + ";";
	sqlite3_stmt* statement;


	if (sqlite3_prepare_v2(pdb, sqlCommand.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		result = 0;
		result = sqlite3_step(statement);
		if (result == SQLITE_ROW)
		{
			int index = 2;
			chapterMapInfo = new ChapterMapInfo();
			chapterMapInfo->setChapterID(id);
			chapterMapInfo->setChapterName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			chapterMapInfo->setTileMapName(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
			chapterMapInfo->setCleared((bool)sqlite3_column_int(statement, index++));
			chapterMapInfo->setBonusDeckID(sqlite3_column_int(statement, index++));
			chapterMapInfo->setRewardID(sqlite3_column_int(statement, index++));
			chapterMapInfo->setEnemyWaveJson(reinterpret_cast<const char*>(sqlite3_column_text(statement, index++)));
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
	return chapterMapInfo;
}
