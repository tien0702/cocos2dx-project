#ifndef __ABILITY_DATA_H__
#define __ABILITY_DATA_H__

#include "Ability/ActiveSkill.h"
#include "GameData/Database.h"

using namespace MyGame;

namespace GameData
{
	class AbilityData
	{
	public:
		std::map<int, BaseStat*>* getStats(sqlite3* pdb, std::string abilityName);
		ActiveSkill* getAbilityByID(int id);
	};
}

#endif // !__ABILITY_DATA_H__
