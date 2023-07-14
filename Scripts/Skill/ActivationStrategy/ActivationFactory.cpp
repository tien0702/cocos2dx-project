#include "ActivationFactory.h"

MyGame::SkillActivation* MyGame::ActivationFactory::getActivationByType(ActivationType type)
{
	SkillActivation* activation = nullptr;
	switch (type)
	{
	case MyGame::ActivationType::AoEActi:
		activation = new AoEActivation();
		break;
	case MyGame::ActivationType::ProjectileActi:
		activation = new ProjectileActivation();
		break;
	default:
		break;
	}
	return activation;
}
