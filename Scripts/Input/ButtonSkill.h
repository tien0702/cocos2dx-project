#ifndef __BUTTON_SKILL_H__
#define __BUTTON_SKILL_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Input/Joystick.h"
#include "GTimer.h"
#include "Character/CharacterObserver.h"

USING_NS_CC;

namespace MyGame
{
	enum ButtonState
	{
		None,
		ButtonPress,
		ButtonHold
	};

	class ButtonSkill : public Node
	{
	public:
		ButtonSkill();
		virtual bool init();
		virtual float getTimeHold();
		virtual ButtonState getState();
		virtual Vec2 getDirection();
		virtual void setPositionButton(Vec2 pos);
		virtual void reset();
		virtual void setLocked();
		virtual void setReady();
		virtual void setCooldown(float duration, float maxDuration);

		virtual bool initJoystick(std::string bgPath, std::string thumbPath);
		virtual bool setAvatarSkill(std::string normalIMGPath);
		virtual bool setBackgroundSkillBtn(std::string imgPath);
	protected:
		ui::Button* _button;
		Joystick* _joystick;
		float _radius;

		Sprite* _border;
		Sprite* _iconLock;

		GTimer* _timer;
		ButtonState _state;

		// cooldown
		bool _isCooldown = false;
		float _cooldownTime = 0.0f;
		float _remainingCooldown = 0.0f;
		DrawNode* _cooldownOverlay;
		Label* _remainingCooldownLb;
	protected:
		virtual void update(float dt);
		virtual void updateUI();
		virtual void updateCooldown(float dt);
	};
}

#endif // !__BUTTON_SKILL_H__
