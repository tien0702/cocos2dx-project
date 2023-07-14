#ifndef __WIN_GAME_H__
#define __WIN_GAME_H__

#include "Scene/SummaryGame.h"
#include "ui/CocosGUI.h"


namespace MyGame
{
	class WinGame : public SummaryGame
	{
	public:
		virtual bool init();
		CREATE_FUNC(WinGame);
	protected:// component
		ui::Button* _confirmBT;
	protected:
		virtual bool loadProperties();
		virtual bool loadComponent();
	};
}

#endif // !__WIN_GAME_H__
