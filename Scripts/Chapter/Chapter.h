#ifndef __CHAPTER_H__
#define __CHAPTER_H__

#include "cocos2d.h"
#include "GameReward/Reward.h"
#include "GameReward/BonusRenderer.h"
#include "Entity/EntityObserver.h"

USING_NS_CC;

namespace MyGame
{
	class GameMap;
	class Chapter
	{
	public:
		Chapter();
	public:
		bool isCompleted();
		void nextMap();
		void startChapter();
		void exitChapter();
		void replay();
		void playAt(int index);
		void sumaryChap(bool isWin);
		void applyBonus(Bonus* bonus);
		void clearBonuses();
		int getCurrentIndexMap() { return _curMap; }
		void giveReward();

	private:
		CC_SYNTHESIZE(int, _idChapter, IDChapter);
		CC_SYNTHESIZE(std::string, _chapterName, ChapterName);
		CC_SYNTHESIZE(Reward*, _reward, ChapterReward);
		CC_SYNTHESIZE(std::vector<int>, _mapIDs, MapIDs);
		CC_SYNTHESIZE(BonusDeck*, _bonusDeck, BnsDeck);
		std::list<Bonus*>* _bonuses;
		int _curMap;
		bool _isCompleted = false;
	};
}

#endif // !__CHAPTER_H__
