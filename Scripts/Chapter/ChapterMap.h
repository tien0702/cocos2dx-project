#ifndef __CHAPTER_MAP_H__
#define __CHAPTER_MAP_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "UI/HUDLayer.h"
#include "Map/GameMap.h"
#include "Camera/CameraFollow.h"
#include "Combat/InfoTargetEnemy.h"
#include "GameReward/BonusRenderer.h"
#include "GameReward/Chest.h"
#include "GameReward/Reward.h"
#include "Chapter/ChapterMapInfo.h"

USING_NS_CC;

namespace MyGame
{
	class Gate;
	class EnemyWave;
	class Chapter;

	class SceneLayer
	{
	public:
		static const int Default = 0;
		static const int Map = 1;
		static const int Effect = 3;
		static const int EntityObject = 4;
		static const int HUDlayer = 5;
	};

	class ChapterMap : public Scene
	{
	public:
		static Scene* createChapterMap(int id);
	public: // set - get
	public:
		void startChapter(Chapter* chapter);
		void nextWave();
		void playWaveAt(int index);
		void exitMap();
		void onCompletedChapter();
		GameMap* getGameMap() { return this->_map; }
	private:
		// properties
		CC_SYNTHESIZE(int, _chapterMapID, ChapterMapID);
		CC_SYNTHESIZE(ChapterMapInfo*, _chapterMapInfo, Info);

		Chapter* _chapter;
		Character* _player;
		InfoTargetEnemy* _infoTargetEnemy;
		GameMap* _map;
		CameraFollow* _camFollow;
		Gate* _gate;

		BonusRenderer* _bonusRenderer;
		Chest* _chest;
		Reward* _reward;
	private:
		// Waves
		std::vector<EnemyWave*> _waves;
		int _curWave = 0;
		bool _isCompleted = false;
		bool _canNextMap = false;

	private:
		CREATE_FUNC(ChapterMap);
		virtual bool init();
		PhysicsWorld* _world;
		void SetPhysicsWorld(PhysicsWorld* world) { this->_world = world; }
		void update(float dt);
	private:
		bool loadProperties();
		bool loadComponent();
		bool loadReward();
		bool initMap();
		bool playerSetting();
		bool initEnemyWaves();
		bool initBonusDeck();

		void startWave();
		void giveReward();
	};
}

#endif // !__CHAPTER_MAP_H__
