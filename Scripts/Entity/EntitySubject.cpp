#include "EntitySubject.h"
#include "EntityObserver.h"

void MyGame::EntitySubject::attach(EntityObserverType type, EntityObserver* ob)
{
	if (ob == nullptr) return;

	if (_observers.find(type) == _observers.end())
	{
		list<EntityObserver*>* obList = new list<EntityObserver*>();
		auto newType = pair<EntityObserverType, list<EntityObserver*>*>(type, obList);
		_observers.insert(newType);
	}

	_observers.at(type)->push_back(ob);
}

void MyGame::EntitySubject::dettach(EntityObserverType type, EntityObserver* ob)
{
	if (_observers.find(type) == _observers.end() || ob == nullptr) return;
	_observers.at(type)->remove(ob);
}

void MyGame::EntitySubject::notifyAllObserver(EntityObserverType type)
{
	// Get list observer by type
	if (_observers.find(type) == _observers.end()) return;
	list<EntityObserver*>* obList = _observers.at(type);

	// Get and check callback by type
	NotifyObserverCallBack callbackByType = getObserverCallbackByType(type);
	if (callbackByType == nullptr)
	{
		return;
	}

	// notify observers
	for (EntityObserver* ob : *obList)
	{
		(ob->*callbackByType)();
	}

}

void MyGame::EntitySubject::dettachAllObject()
{
	_observers.clear();
}

MyGame::NotifyObserverCallBack MyGame::EntitySubject::getObserverCallbackByType(EntityObserverType type)
{
	NotifyObserverCallBack callbackByType = nullptr;

	switch (type)
	{
	case MyGame::EntityObserverType::OnTakeDame:
		callbackByType = &EntityObserver::onTakeDame;
		break;
	case MyGame::EntityObserverType::OnDie:
		callbackByType = &EntityObserver::onDie;
		break;
	case MyGame::EntityObserverType::OnRebornHP:
		callbackByType = &EntityObserver::onRebornHp;
		break;
	case MyGame::EntityObserverType::OnRecoveryHP:
		callbackByType = &EntityObserver::onRecoveryHP;
		break;
	case MyGame::EntityObserverType::OnTakeMP:
		callbackByType = &EntityObserver::onTakeMp;
		break;
	case MyGame::EntityObserverType::OnRecoveryMP:
		callbackByType = &EntityObserver::onRecoveryMp;
		break;
	case MyGame::EntityObserverType::OnRebornMP:
		callbackByType = &EntityObserver::onRebornMp;
		break;
	default:
		break;
	}

	return callbackByType;
}
