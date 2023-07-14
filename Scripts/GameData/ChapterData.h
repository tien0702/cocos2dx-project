#ifndef __CHAPTER_DATA_H__
#define __CHAPTER_DATA_H__

#include "Chapter/Chapter.h"
#include "Chapter/ChapterInfo.h"
#include "Enemy/Enemy.h"
#include "Chapter/EnemyWave.h"
#include "GameData/Database.h"
#include "Chapter/ChapterMapInfo.h"

using namespace MyGame;

namespace GameData
{
	class ChapterData
	{
	public:
		Chapter* getChapterByID(int id);
		ChapterInfo* getChapterInfoByID(int id);
		std::vector<int> getChapterMapsByChapterName(sqlite3* pdb, std::string chapterName);
		std::vector<EnemyWave*> getEnemyWaveInChapterMap(int chapterMapID);
		ChapterMapInfo* getChapterMapInfoByID(int id);
	};
}

#endif // !__CHAPTER_DATA_H__
