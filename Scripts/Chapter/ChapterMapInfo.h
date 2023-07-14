#ifndef __CHAPTER_MAP_INFO_H__
#define __CHAPTER_MAP_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	class ChapterMapInfo
	{
	private:
		CC_SYNTHESIZE(int, _chapterID, ChapterID);
		CC_SYNTHESIZE(int, _bonusDeckID, BonusDeckID);
		CC_SYNTHESIZE(int, _rewardID, RewardID);
		CC_SYNTHESIZE(bool, _isCleared, Cleared);
		CC_SYNTHESIZE(std::string, _chapterName, ChapterName);
		CC_SYNTHESIZE(std::string, _tileMapName, TileMapName);
		CC_SYNTHESIZE(std::string, _enemyWaveJson, EnemyWaveJson);
	};
}

#endif // !__CHAPTER_MAP_INFO_H__
