#include "AoEDelayActivation.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Enemy/Enemy.h"
#include "Manager/GameManager.h"
#include "ObjectTag.h"

void MyGame::AoEDelayActivation::activate(Skill* skill, Vec2 position,float rotation, Vec2 direction)
{

}

void MyGame::AoEDelayActivation::dealDamage()
{

}

std::list<Node*>* MyGame::AoEDelayActivation::getEnemiesInArea()
{
	auto children = GameManager::getIns()->getCurrentMap()->getChildren();

	std::list<Node*>* enemies = new std::list<Node*>();
	for (auto child : children)
	{
		if (child->getTag() == ObjectTag::Enemy)
		{
			enemies->push_back(child);
		}
	}

	return enemies;
}

void MyGame::AoEDelayActivation::playAnimation(Vec2 position)
{

}
