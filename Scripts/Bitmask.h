#ifndef __BITMASK_H__
#define __BITMASK_H__

#include "cocos2d.h"

class Bitmask
{
public:
	class BitmaskContactTest
	{
	public:
		static const int Player = 0x01;
		static const int Projectile = 0x01;
		static const int Enemy = 0x01;
	};

	class Collision_Group
	{
	public:
		static const int Player = 0x01;
		static const int Projectile = 0x01;
		static const int Enemy = 0x01;
	};

	class BitmaskCategory
	{
	public:
		static const int Player = 0x01;
		static const int Projectile = 0x03;
		static const int Enemy = 0x01;
	};

	class BitmaskCollision
	{
	public:
		static const int Player = 0x03;
		static const int Projectile = 0x03;
		static const int Enemy = 0x02;
		static const int ActiveSkill = 0x001;
	};
};


#endif // !__BITMASK_H__
