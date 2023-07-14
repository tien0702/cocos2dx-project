#ifndef __DETECT_ENTITY_H__
#define __DETECT_ENTITY_H__

#include "cocos2d.h"
#include "Character/Character.h"

USING_NS_CC;

namespace MyGame
{
	class DetectEntity
	{
	public:
		// maxRange = 0 means no limit
		static Node* getNearestEnemy(Node* owner, float maxRange);
		static std::vector<Node*>* findEnemiesAround(Node* owner, float range);
		static Node* findCharacter();
		static Character* getCharacter();
	};
}

#endif // !__DETECT_ENTITY_H__
