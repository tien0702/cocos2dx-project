#ifndef __PLAYER_INPUT_H__
#define __PLAYER_INPUT_H__

#include "cocos2d.h"
#include "Input/ButtonNormalATK.h"
#include "Input/ButtonSkill.h"
#include "Input/JoystickMove.h"

USING_NS_CC;

namespace MyGame
{
	enum class InputID
	{
		BT_NormalATK,
		BT_JoystickMove,
		BT_Skill_Ultimate,
		BT_Skill_Talen,
		BT_Skill_Dash
	};

	class PlayerInput : public Layer
	{
	public:
		static PlayerInput* getIns();
		bool getInput(InputID id);
		void cleanInput();
		void waitInDuration(float duration);
		void disable();
		void enable();
		bool isEnable();
		void reloadSkillBtns();

		ButtonSkill* getInputSkill(InputID id);
		float getInputTime(InputID id);
	private:
		static PlayerInput* _instance;
		PlayerInput();
		bool init();

		bool _enable;
		JoystickMove* _joystickMove;
		ButtonNormalATK* _buttonNormalATK;
		ButtonSkill* _ultimate;
		ButtonSkill* _talen;
		ButtonSkill* _evade;
	};
}

#endif // !__PLAYER_INPUT_H__
