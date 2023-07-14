#include "CharacterSubject.h"
#include "CharacterObserver.h"

void MyGame::CharacterSubject::attachCharacter(int idType, CharacterObserver* ob)
{
	if (!this->ID_IsExists(idType))
	{
		std::list<CharacterObserver*> obs;
		auto newObserver = std::pair<int, std::list<CharacterObserver*>>(idType, obs);
		_observers.insert(newObserver);
	}

	_observers.at(idType).push_back(ob);
}

void MyGame::CharacterSubject::dettachCharacter(int idType, CharacterObserver* ob)
{
	if (!this->ID_IsExists(idType)) return;
	_observers.erase(idType);
}

void MyGame::CharacterSubject::notifyAllObservers(int idType)
{
	if (!this->ID_IsExists(idType)) return;

	std::list<CharacterObserver*> obs = _observers.at(idType);
	for (CharacterObserver* ob : obs)
	{
		ob->observerUpdateByID(idType);
	}
}

bool MyGame::CharacterSubject::ID_IsExists(int idType)
{
	if (_observers.find(idType) == _observers.end()) return false;
	return true;
}
