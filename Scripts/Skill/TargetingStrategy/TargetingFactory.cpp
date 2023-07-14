#include "TargetingFactory.h"
#include "TargetSelectArea.h"
#include "TargetProjectile.h"

MyGame::SkillTargeting* MyGame::TargetingFactory::getTargetingByType(TargetingType type)
{
	SkillTargeting* targeting = nullptr;
	switch (type)
	{
	case MyGame::TargetingType::AreaAroundSelf:
		break;
	case MyGame::TargetingType::Projectile:
		targeting = new TargetProjectile();
		break;
	case MyGame::TargetingType::SelectArea:
		targeting = new TargetSelectArea();
		break;
	case MyGame::TargetingType::TargetSelf:
		break;
	case MyGame::TargetingType::SelectEnemy:
		break;
	default:
		break;
	}
    return targeting;
}
