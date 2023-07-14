#ifndef __CHARACTER_WINDOW_VIEW_H__
#define __CHARACTER_WINDOW_VIEW_H__

#include "Player/Player.h"
#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class CharacterWindowView : public Sprite
	{
	public:
		bool init();

	private:
		CC_SYNTHESIZE(Size, _windowSize, WindowSize);
		Sprite* _characterVisual;
		int AniTag = 1;
	private:
		bool loadCompnent();
		void changeAnimation();
		bool isTouchInsideBackground(cocos2d::Touch* touch);
	};
}

#endif // !__CHARACTER_WINDOW_VIEW_H__
