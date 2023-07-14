#include "Projectile.h"
#include "Manager/GameManager.h"
#include "Projectile/ProjectilePool.h"
#include "Bitmask.h"
#include "Entity/Entity.h"
#include "DamagerSystem/DamageMessage.h"
#include "ui/Effect.h"
#include "Manager/GameManager.h"
#include "ObjectTag.h"

bool MyGame::Projectile::init()
{
	if (!Sprite::init()) {
		log("Init Projectile failed!");
		return false;
	}

	// Visual
	std::string pathObj, pathDestroy, plist = ".plist", imgFile = ".png";
	pathObj = "FHD/Projectile/" + _spriteFileName;
	pathDestroy = "FHD/Projectile/" + _aniPath;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pathObj + plist, pathObj + imgFile);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pathDestroy + plist, pathDestroy + imgFile);

	_objAni = Effect::createAnimation(_spriteFileName).first;
	_objAni->setDelayPerUnit(0.05f);
	_destroyAni = Effect::createAnimation(_aniPath).first;
	_objAni->retain();
	_destroyAni->retain();
	_visual = Sprite::createWithSpriteFrame(_objAni->getFrames().front()->getSpriteFrame());
	_visual->runAction(RepeatForever::create(Animate::create(_objAni)));

	//
	auto body = PhysicsBody::createCircle(_radius, PhysicsMaterial(1, 0, 1));
	body->setCollisionBitmask(Bitmask::BitmaskCollision::Projectile);
	body->setContactTestBitmask(Bitmask::BitmaskCollision::Projectile);
	body->setCategoryBitmask(Bitmask::BitmaskCollision::Projectile);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	// Collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MyGame::Projectile::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	//this->scheduleUpdate();

	// addChild
	this->setTag(ObjectTag::Projectile);
	this->addChild(_visual);
	return true;
}

void MyGame::Projectile::triggered(Vec2 direction, Vec2 pos)
{
	// Rotation
	float rotaion = Vec2::angle(Vec2::ANCHOR_BOTTOM_RIGHT, direction);
	if (direction.y > 0)
		rotaion = -rotaion;
	_visual->setRotation(CC_RADIANS_TO_DEGREES(rotaion));

	// Update properties
	_originPos = pos;
	this->setPosition(pos);

	// set up
	direction.normalize();
	_physicsBody->setEnabled(true);
	_physicsBody->setVelocity(direction * _speed);

	// Add to map
	auto map = GameManager::getIns()->getCurrentMap();
	if (map != nullptr)
	{
		map->addChild(this);
		map->setBehindObj(this);
	}
}

void MyGame::Projectile::destroy()
{
	_physicsBody->setEnabled(false);
	this->getParent()->removeChild(this, false);
	_physicsBody->setVelocity(Vec2::ZERO);
	ProjectilePool::getIns()->push(this);
}

bool MyGame::Projectile::onContactBegin(const PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getNode() != this && b->getNode() != this) return false;
	if (((a->getCollisionBitmask() == _physicsBody->getCollisionBitmask()) && (b->getCollisionBitmask() == Bitmask::BitmaskCollision::Enemy)) ||
		((a->getCollisionBitmask() == Bitmask::BitmaskCollision::Enemy) && (b->getCollisionBitmask() == _physicsBody->getCollisionBitmask())))
	{
		Node* nodePlayer = (a->getNode() == this) ? (b->getNode()) : (a->getNode());
		Entity* enemy = dynamic_cast<Entity*>(nodePlayer);
		if (enemy == nullptr) return false;

		float critRate = _owner->getEntityStatByID(7)->getFinalValue() * 0.001f;
		DamageMessage* data = DamageMessage::calculateDamage(_owner, enemy, _power, critRate);
		enemy->takeDamage(data);
		this->destroy();
		return true;
	}

	return true;
}

void MyGame::Projectile::update(float dt)
{
	if (!inRange()) this->destroy();
	else if (!canMoveOnMeta()) this->destroy();
}

void MyGame::Projectile::fixedUpdate(float dt)
{
}

bool MyGame::Projectile::canMoveOnMeta()
{
	GameMap* map = GameManager::getIns()->getCurrentMap();
	int metaType = map->getMetaAtPos(_position);
	if (metaType == MetaType::insideRed) return false;
	return true;
}

bool MyGame::Projectile::inRange()
{
	return (_position.distance(_originPos) < _range);
}
