#include "DetectEntity.h"
#include "ObjectTag.h"
#include "GameConfig.h"

Node* MyGame::DetectEntity::getNearestEnemy(Node* owner, float maxRange)
{
	Scene* runningScene = Director::getInstance()->getRunningScene();
	if (runningScene == nullptr) return nullptr;

	// Get map
	Node* map = runningScene->getChildByTag(ObjectTag::ChapterMap)->getChildByTag(ObjectTag::Map);
	if (map == nullptr) return nullptr;
	Vector<Node*> children = map->getChildren();

	// Get all child with tag Enemy
	Vector<Node*> enemies;
	std::for_each(children.begin(), children.end(),
		[&](Node*& child) {
			if (child->getTag() == ObjectTag::Enemy) {
				enemies.pushBack(child);
			}
		});
	if (enemies.empty()) return nullptr;
	// Find enemy
	Node* resultEnemy = nullptr;
	float disNearest = 0.0f;
	std::for_each(enemies.begin(), enemies.end(),
		[&](Node*& enemy) {
			float distance = owner->getPosition().distance(enemy->getPosition());
			if (distance > maxRange) return;
			if (resultEnemy != nullptr)
			{
				if (distance < disNearest)
				{
					resultEnemy = enemy;
					disNearest = distance;
				}
			}
			else
			{
				resultEnemy = enemy;
				disNearest = distance;
			}
		}
	);

	return resultEnemy;
}

std::vector<Node*>* MyGame::DetectEntity::findEnemiesAround(Node* owner, float range)
{

	Scene* runningScene = Director::getInstance()->getRunningScene();
	if (runningScene == nullptr) return nullptr;

	// Get map
	Node* map = runningScene->getChildByTag(ObjectTag::ChapterMap)->getChildByTag(ObjectTag::Map);
	if (map == nullptr) return nullptr;
	Vector<Node*> children = map->getChildren();

	// Get all child with tag Enemy
	Vector<Node*> enemies;
	std::for_each(children.begin(), children.end(),
		[&](Node*& child) {
			if (child->getTag() == ObjectTag::Enemy) {
				enemies.pushBack(child);
			}
		});
	if (enemies.empty()) return nullptr;

	// Find enemy around
	std::vector<Node*>* result = new std::vector<Node*>();

	std::for_each(enemies.begin(), enemies.end(),
		[&](Node*& enemy) {
			float distance = owner->getPosition().distance(enemy->getPosition());
			if (distance > range) return;
			result->push_back(enemy);
		}
	);


	return result;
}

Node* MyGame::DetectEntity::findCharacter()
{
	Scene* runningScene = Director::getInstance()->getRunningScene();
	if (runningScene == nullptr) return nullptr;

	// Get map
	Node* map = runningScene->getChildByTag(ObjectTag::ChapterMap)->getChildByTag(ObjectTag::Map);
	if (map == nullptr) return nullptr;

	// Get Character 
	Node* character = nullptr;
	character = map->getChildByTag(ObjectTag::Player);

	return character;
}

MyGame::Character* MyGame::DetectEntity::getCharacter()
{
	Node* findChar = DetectEntity::findCharacter();

	Character* character = dynamic_cast<Character*>(findChar);

	return character;
}
