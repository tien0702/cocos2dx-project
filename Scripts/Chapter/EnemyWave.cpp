#include "EnemyWave.h"
#include "Chapter/ChapterMap.h"
#include "GameData/EntityData.h"
#include "ObjectTag.h"
#include "Enemy/EnemyPool.h"


#include "Enemy/EnemyPool.h"

#include "json/rapidjson.h"
#include "json/document.h"

MyGame::EnemyWave::EnemyWave()
{
}

bool MyGame::EnemyWave::initWave()
{
	for (auto info : _infoEnemies)
	{
		Enemy* enemy = EnemyPool::getIns()->getEnemyByName(info.first);
		if (enemy == nullptr) continue;

		enemy->setLevel(info.second);
		_enemies.push_back(enemy);
	}
	return !_enemies.empty();
}

void MyGame::EnemyWave::enter(ChapterMap* chapterMap)
{
	if (chapterMap == nullptr)return;
	_chapterMap = chapterMap;
	GameMap* map = _chapterMap->getGameMap();
	for (int i = 0; i < _enemies.size(); ++i)
	{
		_enemies.at(i)->attach(EntityObserverType::OnDie, this);
		std::pair<Vec2, Rect> result = map->randomPos(MetaType::outside);
		Vec2 pos = result.first;
		_enemies.at(i)->setPosition(pos);
		_enemies.at(i)->setEnemySpawnArea(result.second);
		map->addChild(_enemies.at(i));
		map->setBehindObj(_enemies.at(i));
	}

	for (auto enemy : _enemies)
	{
		enemy->spawn();
	}
}

void MyGame::EnemyWave::exit()
{
	//_enemies.clear();
	/*for (Enemy* e : _enemies)
	{
		e->detachOnDead(this);
	}*/
}

void MyGame::EnemyWave::setInfoEnemies(vector<pair<string, int>> infoEnemies)
{
	_infoEnemies = infoEnemies;
}

vector<pair<string, int>> MyGame::EnemyWave::getInfoEnemies()
{
	return _infoEnemies;
}

void MyGame::EnemyWave::onDead()
{
	Node* hasEnemy = _chapterMap->getGameMap()->getChildByTag(ObjectTag::Enemy);
	if (hasEnemy == nullptr) this->completedWave();
}

void MyGame::EnemyWave::onDie()
{
	Node* hasEnemy = _chapterMap->getGameMap()->getChildByTag(ObjectTag::Enemy);
	if (hasEnemy == nullptr) this->completedWave();
}

void MyGame::EnemyWave::onTakingDamage()
{
}

void MyGame::EnemyWave::completedWave()
{
	_isCompleted = true;
}
