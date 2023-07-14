#ifndef __CHARACTER_SUBJECT_H__
#define __CHARACTER_SUBJECT_H__

#include "cocos2d.h"

namespace MyGame
{
	class CharacterObserver;
	class CharacterSubject
	{
	public:
		virtual void attachCharacter(int idType, CharacterObserver* ob);
		virtual void dettachCharacter(int idType, CharacterObserver* ob);
		virtual void notifyAllObservers(int idType);
	protected:
		std::map<int, std::list<CharacterObserver*>> _observers;
		bool ID_IsExists(int idType);
	};
}

#endif // !__CHARACTER_SUBJECT_H__
