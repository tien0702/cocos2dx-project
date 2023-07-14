#ifndef __BUTTON_NORMAL_ATK_H__
#define __BUTTON_NORMAL_ATK_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GTimer.h"
#include "Input/ButtonSkill.h"

USING_NS_CC;

namespace MyGame
{
	class ButtonNormalATK : public ui::Button
	{
	public:
		static ButtonNormalATK* getIns();
		virtual float getTimeHold();
		virtual ButtonState getState();
	protected:
		static ButtonNormalATK* _instance;
		ButtonNormalATK();
		virtual bool init();
		GTimer* _timer;
		ButtonState _state;
	};
}

#endif // !__BUTTON_NORMAL_ATK_H__
