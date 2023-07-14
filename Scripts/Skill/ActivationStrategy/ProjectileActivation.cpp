#include "ProjectileActivation.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Character/Character.h"
#include "Skill/StateMachine/SkillStateMachine.h"
#include "ObjectTag.h"
#include "Entity/DetectEntity.h"
#include "Enemy/Enemy.h"
#include "UI/Effect.h"
#include "Bitmask.h"
#include "Manager/GameManager.h"
#include "AudioManager/AudioManager.h"


void MyGame::ProjectileActivation::activate(Skill* skill, Vec2 position, float rotation, Vec2 direction)
{
	_skill = skill;
	if (!_isLoaded) loadProjectile();
	takeMana();
	_isExplosive = false;
	setupForProjectile(position, rotation);
	Director::getInstance()->getRunningScene()->addChild(this);
	AudioManager::getIns()->playEffect("Audio/use-skill.mp3");

	// shoot out projectile
	playAnimationShootOut();
	shootOut(direction);

	this->scheduleUpdate();
}

void MyGame::ProjectileActivation::shootOut(Vec2 direction)
{
	direction.normalize();
	float speed = _skill->getStatByID(Stat::MoveSpeed)->getFinalValue();
	Vec2 velocity = direction * speed;
	_projectileVisual->getPhysicsBody()->setVelocity(velocity);
}

void MyGame::ProjectileActivation::preExplosive()
{
	_isExplosive = true;
	this->unscheduleUpdate();
	_projectileVisual->stopActionByTag(TagAnimation);
	_projectileVisual->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

void MyGame::ProjectileActivation::explosive()
{
	preExplosive();
	autoExit();
	dealDamage();
}

void MyGame::ProjectileActivation::playAnimationShootOut()
{
	Animation* animation = AnimationCache::getInstance()->getAnimation(_skill->getInfo()->getEffectName());
	Animate* animate = Animate::create(animation);
	RepeatForever* aniReapeat = RepeatForever::create(animate);
	aniReapeat->setTag(TagAnimation);
	_projectileVisual->runAction(aniReapeat);
}

void MyGame::ProjectileActivation::playAnimationExplosive()
{
	std::string animationName = _skill->getInfo()->getEffectName() + "-impact";
	Animation* animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate* animate = Animate::create(animation);
	_timeOut = animate->getDuration();
	_projectileVisual->runAction(animate);
}

void MyGame::ProjectileActivation::update(float dt)
{
	if (!insideMetaAllow() || isOutRange())
	{
		playAnimationExplosive();
		explosive();
	}
}

void MyGame::ProjectileActivation::dealDamage()
{
	float aoe = _skill->getStatByID(Stat::AoERadius)->getFinalValue();
	auto enemies = DetectEntity::findEnemiesAround(_projectileVisual, aoe);
	AudioManager::getIns()->playEffect("Audio/" + _skill->getInfo()->getEffectName() + ".mp3");

	if (enemies == nullptr) return;
	for (auto enemyNode : *enemies)
	{
		Enemy* enemy = static_cast<Enemy*>(enemyNode);
		if (enemy == nullptr) continue;

		float critRate = _skill->getOwner()->getEntityStatByID(Stat::CritRate)->getFinalValue() * 0.001f;
		DamageMessage* dameData = DamageMessage::calculateDamage(_skill->getOwner(), enemy, *_skill->getSkillPower(), critRate);
		enemy->takeDamage(dameData);
	}
}

void MyGame::ProjectileActivation::setupForProjectile(Vec2 position, float rotation)
{
	_originPos = position;
	_projectileVisual->setPosition(position);
	_projectileVisual->setRotation(rotation);
	GameManager::getIns()->getCurrentMap()->addChild(_projectileVisual);
	GameManager::getIns()->getCurrentMap()->setBehindObj(_projectileVisual);
}

void MyGame::ProjectileActivation::autoExit()
{
	auto action = Sequence::createWithTwoActions(DelayTime::create(_timeOut),
		CallFunc::create([=]() {this->exit();
			}));
	_projectileVisual->runAction(action);
}

void MyGame::ProjectileActivation::exit()
{
	_projectileVisual->removeFromParent();
	_projectileVisual->stopAllActions();
	this->removeFromParent();
}

bool MyGame::ProjectileActivation::loadProjectile()
{
	_isLoaded = true;

	std::string path = "FHD/Effect/";
	// load animation shoot out
	std::string effectName = _skill->getInfo()->getEffectName();
	Effect::loadAnimationCacheWithFile(path, effectName, effectName);
	
	// load animation explosive
	std::string effectImpactName = _skill->getInfo()->getEffectName() + "-impact";
	Effect::loadAnimationCacheWithFile(path, effectImpactName, effectImpactName);
	
	// init variable _projectile
	Animation* ani = AnimationCache::getInstance()->getAnimation(effectName)->clone();
	_projectileVisual = Sprite::createWithSpriteFrame(ani->getFrames().front()->getSpriteFrame());
	_projectileVisual->retain();
	_projectileVisual->setTag(ObjectTag::Player);
	
	// init physicsbody
	initBody();

	return true;
}

bool MyGame::ProjectileActivation::initBody()
{
	Size bodySize;
	bodySize.width = _skill->getStatByID(Stat::AoEWidth)->getFinalValue();
	bodySize.height = _skill->getStatByID(Stat::AoEHeight)->getFinalValue();
	PhysicsBody* body = PhysicsBody::createEdgeBox(bodySize, PhysicsMaterial(1, 0, 1), 1);
	body->setContactTestBitmask(Bitmask::BitmaskContactTest::Player);
	body->setCollisionBitmask(Bitmask::BitmaskCollision::Player);
	body->setCategoryBitmask(Bitmask::BitmaskCategory::Player);
	_projectileVisual->setPhysicsBody(body);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MyGame::ProjectileActivation::onContactBegin, this);
	_projectileVisual->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}

bool MyGame::ProjectileActivation::onContactBegin(PhysicsContact& contact)
{
	if (_isExplosive) return false;
	Node* a = contact.getShapeA()->getBody()->getNode();
	Node* b = contact.getShapeB()->getBody()->getNode();

	if (a != _projectileVisual && b != _projectileVisual) return false;

	if (!((a->getTag() == ObjectTag::Player && b->getTag() == ObjectTag::Enemy) ||
		((a->getTag() == ObjectTag::Enemy && b->getTag() == ObjectTag::Player))))
	{
		return false;
	}

	playAnimationExplosive();
	explosive();

	return true;
}

bool MyGame::ProjectileActivation::isOutRange()
{
	float maximumProjectileRange = _skill->getStatByID(Stat::MaximumProjectileRange)->getFinalValue();
	float distace = _originPos.distance(_projectileVisual->getPosition());
	return (distace > maximumProjectileRange);
}

bool MyGame::ProjectileActivation::insideMetaAllow()
{
	Vec2 projectilePos = _projectileVisual->getPosition();
	GameMap* map = GameManager::getIns()->getCurrentMap();
	int metaType = map->getMetaAtPos(projectilePos);
	return (metaType != MetaType::insideRed);
}
