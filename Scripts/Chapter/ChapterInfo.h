#ifndef __CHAPTER_INFO_H__
#define __CHAPTER_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	enum class ChapterState
	{
		Uncompleted,
		Completed,
		Unopened
	};
	class ChapterInfo
	{
	protected:
		CC_SYNTHESIZE(int, _chapterID, ChapterID);
		CC_SYNTHESIZE(std::string, _chapterName, ChapterName);
		CC_SYNTHESIZE(int, _rewardID, RewardID);
		CC_SYNTHESIZE(ChapterState, _state, State);
		CC_SYNTHESIZE(std::vector<int>, _mapIDs, MapIDs);
	};
}

#endif // !__CHAPTER_INFO_H__
