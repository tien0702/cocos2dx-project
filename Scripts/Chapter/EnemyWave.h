#ifndef __CHAPTER_MAP_PART_H__
#define __CHAPTER_MAP_PART_H__

#include "cocos2d.h"
#include "Entity/EntityObserver.h"

using namespace std;

namespace MyGame
{
	class Enemy;
	class ChapterMap;

	class EnemyWave : public EntityObserver
	{
	public:
		EnemyWave();
		bool initWave();
		bool _isCompleted = false;

		void enter(ChapterMap* chapterMap);
		void exit();
		void setInfoEnemies(vector<pair<string, int>> infoEnemies);
		vector<pair<string, int>> getInfoEnemies();
	protected:
		vector<Enemy*> _enemies;
		ChapterMap* _chapterMap;
		vector<pair<string, int>> _infoEnemies;
	protected:
		virtual void onDead();
		virtual void onDie();
		virtual void onTakingDamage();
		virtual void completedWave();
	};
}

#endif // !__CHAPTER_MAP_PART_H__
