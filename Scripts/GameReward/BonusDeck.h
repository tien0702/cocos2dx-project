#ifndef __BONUS_DECK_H__
#define __BONUS_DECK_H__

#include "GameReward/BonusCard.h"

namespace MyGame
{
	class Entity;
	class BonusDeck
	{
	public:
		BonusDeck();

		BonusCard* takeBonusCard();
		std::vector<BonusCard*> takeBonusCard(int amount);
		void shuffle();
		void addBonus(std::string name, Bonus* bns);
		void removeCard(BonusCard* card);
	private:
		CC_SYNTHESIZE(Entity*, _entity, TargetEntity);
		std::vector<BonusCard*>* _bonuses;
	};
}

#endif // !__BONUS_DECK_H__
