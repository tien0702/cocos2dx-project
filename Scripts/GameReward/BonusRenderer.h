#ifndef __BONUS_RENDERER_H__
#define __BONUS_RENDERER_H__

#include "cocos2d.h"
#include "GameReward/BonusDeck.h"

USING_NS_CC;

namespace MyGame
{
	class BonusRenderer : public Layer
	{
	public:
		static const int CardTag = 1;
	public:
		bool init();
		void showing();
		void disable();
		BonusRenderer(BonusDeck* bonusDeck);
	private:
		std::vector<BonusCard*> getCards();
		void calculatePosition(std::vector<BonusCard*> cards);
		void selectCard(BonusCard* target);
		void useBonus();
		void checkRefreshBtn();
	private:
		CC_SYNTHESIZE(BonusDeck*, _bonusDeck, Deck);
		BonusCard* _bonusCardTarget = nullptr;
		ui::Button* _selectBT, *_refresh;
		LayerColor* _darkColor;
		std::vector<MyGame::BonusCard*> _cards;
		bool _isShowing = false;
		int _numberCard = 3;
	};
}

#endif // !__BONUS_RENDERER_H__
