#include "CharacterObserver.h"

void MyGame::CharacterObserver::observerUpdateByID(int idType)
{
	switch (idType)
	{
	case ObserverType::ChangeWeapon:
		this->onChangeWeapon();
		break;
	case ObserverType::UseUltimate:
		this->onUseUltimate();
		break;
	case ObserverType::UseTalen:
		this->onUseTalen();
		break;
	case ObserverType::UseDash:
		this->onUseDash();
		break;
	case ObserverType::UseNormalAttack:
		this->onUseNormalAttack();
		break;
	default:
		break;
	}
}
