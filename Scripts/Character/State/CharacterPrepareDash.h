#ifndef __CHARACTER_PREPATE_DASH_H__
#define __CHARACTER_PREPATE_DASH_H__

#include "Character/State/CharacterState.h"
#include "ui/CocosGUI.h"

namespace MyGame
{
	class ActiveSkill;
	class ButtonSkill;

	class CharacterPrepareDash : public CharacterState
	{
	public:
		void enter(Character* owner);
		std::string updateState(float dt);
		void exit();

		CharacterPrepareDash();
	private:
		ui::LoadingBar* _powerBar;

		ButtonSkill* _targetInput;
		ActiveSkill* _dashAbility;


		float _elapsedTime;
		float _timeHold;
		float _maxTimeHold;
		float _originalTimeHold;
	private:
		bool initAnimation();
		bool loadProperties();

		void updatePowerBar();
		void flipX();
		bool checkInput();
		void updatePowerRate();
	};
}

#endif // !__CHARACTER_PREPATE_DASH_H__
