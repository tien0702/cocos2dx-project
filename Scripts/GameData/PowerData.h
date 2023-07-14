#ifndef __POWER_DATA_H__
#define __POWER_DATA_H__

#include "DamagerSystem/Power.h"

using namespace MyGame;

namespace GameData
{
	class PowerData
	{
	public:
		Power* getPowerByID(int id);
	};
}

#endif // !__POWER_DATA_H__
