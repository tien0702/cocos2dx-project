#include "Database.h"

GameData::Database* GameData::Database::_instance;
const std::string GameData::Database::_dbName = "gameData.sql";

GameData::Database* GameData::Database::getIns()
{
	if (_instance == nullptr) {
		_instance = new Database();
	}
	return _instance;
}

GameData::Database::Database()
{
    sqlite3* pdb;
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "gameData.sql";
	int result = sqlite3_open(path.c_str(), &pdb);

	if (result != SQLITE_OK) {
		log("Open Database failed!");
        sqlite3_close(pdb);
		return;
	}
	log("Open Database succses!");
	auto d = FileUtils::getInstance()->getDataFromFile("sql.sql");
	auto cmmd = d.getBytes();
	std::string cmd = (char*)cmmd;
	result = sqlite3_exec(pdb, cmd.c_str(), NULL, NULL, NULL);

	if (result != SQLITE_OK)
		log("Init database failed!");
	else
		log("Init Database succses!");

    sqlite3_close(pdb);
}

bool GameData::Database::deleteDatabase()
{
    sqlite3* db;
    std::string path = FileUtils::getInstance()->getWritablePath();
    path += "gameData.sql";
    int rc = sqlite3_open(path.c_str(), &db);

    if (rc == SQLITE_OK) {

        const char* sql = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name";
        sqlite3_stmt* stmt = NULL;

        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

        if (rc == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {

                const char* tableName = (const char*)sqlite3_column_text(stmt, 0);

                char* errorMsg = 0;
                const char* dropSql = "DROP TABLE IF EXISTS ";
                std::string query(dropSql);
                query.append(tableName);

                rc = sqlite3_exec(db, query.c_str(), 0, 0, &errorMsg);

                if (rc != SQLITE_OK) {
                    CCLOG("error delete %s: %s", tableName, errorMsg);
                    sqlite3_free(errorMsg);
                }
            }

            sqlite3_finalize(stmt);
        }
        else {
            CCLOG("error get: %s", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
    }
    else {
        CCLOG("error connect: %s", sqlite3_errmsg(db));
    }
    sqlite3_close(db);
	return true;
}
