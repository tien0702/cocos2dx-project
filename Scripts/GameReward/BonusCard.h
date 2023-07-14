#ifndef __BONUS_CARD_H__
#define __BONUS_CARD_H__

#include "Entity/Bonus.h"
#include "GameConfig.h"

#include "ui/CocosGUI.h"

namespace MyGame
{
	class Entity;
	class BonusCard : public ui::Button
	{
	public:
		bool init();
		BonusCard(std::string name, Bonus* bonus);
		void endBonus();
		void setSelected(bool val);
		Bonus* getBonus() { return _bonus; }
		void reveal();
	private:
		CC_SYNTHESIZE(Entity*, _target, TargetEntity);
		std::string _cardName;
		Bonus* _bonus;
		bool _using = false;

		Label* _cardNameLB;
		Label* _cardDescriptionLB;
	public:
		std::string _backgroundPath = "FHD/Background/card-background.png";
		std::string _backgroundPathSelected = "FHD/Background/card-background-selected.png";
		TTFConfig _font = GameConfig::getIns()->getFont();

		std::string getDescription();
	};
}

#endif // !__BONUS_CARD_H__
