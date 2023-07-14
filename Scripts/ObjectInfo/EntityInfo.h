#ifndef __ENEITY_INFO_H__
#define __ENEITY_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	class EntityInfo
	{
	protected:
		CC_SYNTHESIZE(int, _entityID, EntityID);
		CC_SYNTHESIZE(std::string, _entityName, EntityName);
	};
}

#endif // !__ENEITY_INFO_H__
