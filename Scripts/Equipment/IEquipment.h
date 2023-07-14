#ifndef __I_EQUIPMENT_H__
#define __I_EQUIPMENT_H__

#include "cocos2d.h"

namespace MyGame
{
	class IEquipment
	{
	protected:
		CC_SYNTHESIZE(int, _level, Level);
		CC_SYNTHESIZE(bool, _locked, Locked);
		CC_SYNTHESIZE(bool, _equipped, Equipped);
	};
}

#endif // !__I_EQUIPMENT_H__
