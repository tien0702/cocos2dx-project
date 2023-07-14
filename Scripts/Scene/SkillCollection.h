#ifndef __SKILL_COLLECTION_H__
#define __SKILL_COLLECTION_H__

#include "cocos2d.h"
#include "Skill/Skill.h"

USING_NS_CC;

namespace MyGame
{
	class SkillCollection : public Scene
	{
	public:
		bool init();

		CREATE_FUNC(SkillCollection);
	private:
		std::vector<Skill*>* getSkills();
	};
}

#endif // !__SKILL_COLLECTION_H__
