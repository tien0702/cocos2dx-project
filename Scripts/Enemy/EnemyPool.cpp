#include "EnemyPool.h"
#include "GameData/EntityData.h"
#include "UI/Entity/HPBarPool.h"

MyGame::EnemyPool* MyGame::EnemyPool::_instance;

MyGame::EnemyPool::EnemyPool()
{
	_enemies = new std::map<std::string, std::queue<Enemy*>>();
}

MyGame::EnemyPool* MyGame::EnemyPool::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new EnemyPool();
	}

	return _instance;
}

void MyGame::EnemyPool::initEnemyByName(std::string name)
{
	int amountNeeded = 0;
	if (_enemies->find(name) == _enemies->end())
	{
		std::queue<Enemy*> proLst = std::queue<Enemy*>();
		auto newProType = std::pair<std::string, std::queue<Enemy*>>(name, proLst);
		_enemies->insert(newProType);
		amountNeeded = _maxEnemy;
	}
	else
	{
		amountNeeded = _maxEnemy - (_enemies->at(name).size());
	}

	GameData::EntityData* gameData = new GameData::EntityData();

	for (int i = 0; i < amountNeeded; ++i)
	{
		Enemy* enemy = gameData->getEnemyByName(name);
		if (enemy == nullptr)
		{
			log("Enemy %s does not exists!", name.c_str());
			break;
		}
		enemy->init();
		this->push(enemy);
	}

	delete gameData;
}

Enemy* MyGame::EnemyPool::getEnemyByName(std::string name)
{
	Enemy* enemy = nullptr;
	if (_enemies->find(name) == _enemies->end()
		|| _enemies->at(name).size() == 0)
	{
		auto data = new GameData::EntityData();
		enemy = data->getEnemyByName(name);
		enemy->init();
	}
	else
	{
		enemy = _enemies->at(name).front();
		_enemies->at(name).pop();
	}
	if (enemy != nullptr)
	{
		auto hpBar = HPBarPool::getIns()->get();
		hpBar->active(enemy);
	}

	return enemy;
}

void MyGame::EnemyPool::push(Enemy* object)
{
	object->retain();
	object->getHealth()->reborn();
	log("Push %s", object->getEntityName().c_str());

	std::string objName = object->getEntityName();
	if (_enemies->find(objName) == _enemies->end())
	{
		std::queue<Enemy*> proLst = std::queue<Enemy*>();
		proLst.push(object);
		auto newProType = std::pair<std::string, std::queue<Enemy*>>(objName, proLst);
		_enemies->insert(newProType);
	}
	else if (_enemies->at(objName).size() < _maxEnemy)
	{
		_enemies->at(objName).push(object);
	}
}


bool MyGame::EnemyPool::isExists(std::string name)
{
	return (_enemies->find(name) != _enemies->end());
}
