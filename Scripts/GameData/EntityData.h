#ifndef __CHARACTER_DATA_H__
#define __CHARACTER_DATA_H__

#include "Character/Character.h"
#include "GameData/SQLite/sqlite3.h"
#include "GameData/Database.h"
#include "Enemy/Enemy.h"

using namespace MyGame;

namespace GameData
{
	class EntityData
	{
	public:
		EntityData();
		std::list<BaseStat*>* getStats(sqlite3* pdb, int entityID);
		std::list<BaseStat*>* getStats(sqlite3* pdb, std::string entityName);
		Character* getCharacter();
		Enemy* getEnemyByID(int id);
		Enemy* getEnemyByName(std::string name);
		Bonus* getBonusByID(int id);
		BaseStat* getBaseStatByID(int id);
		Stat getStatByID(int id);
		Stat getStatByName(std::string name);
	private:
	};
}

#endif // !__CHARACTER_DATA_H__
