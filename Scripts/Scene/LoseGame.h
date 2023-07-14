#ifndef __LOSE_GAME_H__
#define __LOSE_GAME_H__

#include "Scene/SummaryGame.h"

namespace MyGame
{
	class LoseGame : public SummaryGame
	{
	public:
		virtual bool init();

		CREATE_FUNC(LoseGame);
	protected:// component
		ui::Button* _confirmBT, *_replayBtn;
	protected:
		virtual bool loadProperties();
		virtual bool loadComponent();
		bool canReplay();
		std::string getCostReplay();
	};
}

#endif // !__LOSE_GAME_H__
