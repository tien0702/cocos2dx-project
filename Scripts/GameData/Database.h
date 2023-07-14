#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "cocos2d.h"
#include "GameData/SQLite/sqlite3.h"

USING_NS_CC;

namespace GameData
{
	class Database
	{
	public:
		static Database* getIns();
		bool deleteDatabase();
	private:
		Database();
		static Database* _instance;
		static const std::string _dbName;

	};
}

#endif // !__DATABASE_H__
