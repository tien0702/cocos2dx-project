#ifndef __FLOATING_TEXT_NOTIFY_H__
#define __FLOATING_TEXT_NOTIFY_H__

#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;

namespace MyGame
{
	class FloatingTextNotify
	{
	public:

		// On Screen
		static void onScreenMiddle_Top(std::string content, Color3B color);


		// On Player
		static void onPlayer_Middle(std::string content, Color3B color);

	private:
		static Vec2 getCharPositionOnMap();
	};
}

#endif // !__FLOATING_TEXT_NOTIFY_H__
