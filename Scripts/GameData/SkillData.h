#ifndef __SKILL_DATA_H__
#define __SKILL_DATA_H__

#include "Skill/PassiveSkill.h"
#include "Skill/Skill.h"

using namespace MyGame;

namespace GameData
{
	class SkillData
	{
	public:
		PassiveSkill* getPassiveSkillByID(int id);
		Skill* getSkillByID(int id);
		Skill* getSkillByName(std::string name);
		std::vector<Skill*>* getPlayerSkills();
		std::vector<Skill*>* getSkills();
		std::map<int, BaseStat*> getStatsBySkillName(std::string skillName);

	};
}

#endif // !__SKILL_DATA_H__
