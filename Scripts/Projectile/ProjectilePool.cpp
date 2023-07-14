#include "ProjectilePool.h"
#include "Player/Player.h"
#include "GameData/ItemData.h"

MyGame::ProjectilePool* MyGame::ProjectilePool::_instance;

MyGame::ProjectilePool* MyGame::ProjectilePool::getIns()
{
	if (_instance == nullptr)
		_instance = new ProjectilePool();
	return _instance;
}

MyGame::ProjectilePool::ProjectilePool()
{
	_projectiles = new std::map<int, std::queue<Projectile*>>();
}

MyGame::Projectile* MyGame::ProjectilePool::get(int id)
{
	Projectile* projectile = nullptr;
	if (_projectiles->find(id) == _projectiles->end()
		|| _projectiles->at(id).size() == 0)
	{
		auto data = new GameData::ItemData();
		projectile = data->getProjectileByID(id);
		projectile->init();
	}
	else
	{
		projectile = _projectiles->at(id).front();
		_projectiles->at(id).pop();
	}

	return projectile;
}

void MyGame::ProjectilePool::push(Projectile* object)
{
	object->retain();

	if (_projectiles->find(object->getIDType()) == _projectiles->end())
	{
		std::queue<Projectile*> proLst = std::queue<Projectile*>();
		proLst.push(object);
		auto newProType = std::pair<int, std::queue<Projectile*>>(object->getIDType(), proLst);
		_projectiles->insert(newProType);
	}
	else if(_projectiles->at(object->getIDType()).size() < _maxProjectile)
	{
		_projectiles->at(object->getIDType()).push(object);
	}
}

void MyGame::ProjectilePool::destroyProjectile(int id)
{
	if (_projectiles->find(id) != _projectiles->end())
		_projectiles->erase(id);
}
