#include "Enemy.h"
#include "Entity/EntityObserver.h"
#include "ui/Effect.h"
#include "Bitmask.h"
#include "GameConfig.h"
#include "ObjectTag.h"
#include "ui/FloatingNumber.h"
#include "EnemyPool.h"

#include "Enemy/State/EnemyStateFactory.h"

#include "Manager/GameManager.h"

bool MyGame::Enemy::init()
{
	if (!Entity::init()) {
		log("Init Enemy failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load properties failed!");
		return false;
	}

	if (!initAnimation()) {
		log("Init animation Enemy failed!");
		return false;
	}
	this->initBody();
	this->loadComponent();
	this->loadInfo();

	return true;
}

void MyGame::Enemy::takeDamage(DamageMessage* data)
{
	_entityHealth->takeDamage(data);
	_stateMachine->setState("take-hit");
	FloatingNumber::getIns()->showDamage(_position, data);
	if (this->getHealth()->isDead())
	{
		this->die();
		this->notifyAllObserver(EntityObserverType::OnDie);
	}
}

int MyGame::Enemy::getCurrentStateID()
{
	return _stateMachine->getCurrentState()->getIDState();
}

void MyGame::Enemy::spawn()
{
	_stateMachine->enter(this);
	_entityHealth->reborn();
	this->loadInfo();
}

void MyGame::Enemy::enableRangeVisual(bool enable)
{
	_rangeFindVisual->setVisible(enable);
}

bool MyGame::Enemy::loadProperties()
{
	BaseStat* rangeVisual = this->getEntityStatByID(Stat::RangeFind);
	float rangeVal = rangeVisual->getFinalValue();
	_rangeFindVisual = DrawNode::create();
	_rangeFindVisual->retain();
	_rangeFindVisual->drawCircle(Vec2::ZERO, rangeVal,
		360.0f, 360, false, Color4F::RED);

	_rangeFindVisual->setVisible(false);
	_type = EntityType::EnemyType;
	this->setTag(ObjectTag::Enemy);
	return true;
}

bool MyGame::Enemy::initAnimation()
{
	std::string path, pathPlist, pathPNG, plist = ".plist", imgFile = ".png";

	path = "FHD/Enemy/";
	path += _spriteFileName + "-";
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();

	for (auto stateName : _states)
	{
		spriteCache->addSpriteFramesWithFile(path + stateName + plist, path + stateName + imgFile);
		Animation* ani = Effect::createAnimation(_spriteFileName + "-" + stateName).first;
		ani->retain();
		aniCache->addAnimation(ani, _spriteFileName + "-" + stateName);
	}

	// Init sprite
	auto ani = aniCache->getAnimation(_spriteFileName + "-" + _states.at(0));
	_sprite = Sprite::createWithSpriteFrame(ani->getFrames().front()->getSpriteFrame());
	_sprite->retain();

	return true;
}

bool MyGame::Enemy::initBody()
{
	// Body
	auto body = PhysicsBody::createBox(this->_eneitySize, PhysicsMaterial(1, 0, 1));
	this->setPhysicsBody(body);
	body->setDynamic(true);
	body->setContactTestBitmask(Bitmask::BitmaskContactTest::Enemy);
	body->setCollisionBitmask(Bitmask::BitmaskCollision::Enemy);
	body->setCategoryBitmask(Bitmask::BitmaskCategory::Enemy);
	body->setRotationEnable(false);
	return true;
}

bool MyGame::Enemy::loadComponent()
{
	TTFConfig font = GameConfig::getIns()->getFont();
	font.fontSize = 10;

	// Name and health bar
	std::string infoStr = "Lv. " + std::to_string(_level);
	_infoLv = Label::createWithTTF(font, infoStr);
	_infoLv->setAlignment(TextHAlignment::CENTER);

	Vec2 posInfo;
	posInfo.x = _position.x;
	posInfo.y = _position.y + _eneitySize.height / 2 + _infoLv->getContentSize().height / 2 + 10;

	_infoLv->setPosition(posInfo);
	this->addChild(_infoLv);
	// Collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MyGame::Enemy::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// State Machine
	_stateMachine = new EnemyStateMachine();
	_stateMachine->init(this, _states.at(0), EnemyStateFactory::getEnemyStateByName(_states.at(0)));
	_stateMachine->enter(this);
	for (int i = 1; i < _states.size(); ++i)
	{
		_stateMachine->addState(_states.at(i), EnemyStateFactory::getEnemyStateByName(_states.at(i)));
	}

	this->addChild(_sprite);
	this->addChild(_stateMachine);
	this->addChild(_rangeFindVisual);
	return false;
}

bool MyGame::Enemy::loadInfo()
{
	std::string infoStr = "Lv. " + std::to_string(this->_level);
	_infoLv->setString(infoStr);
	return true;
}

void MyGame::Enemy::update(float dt)
{

}

void MyGame::Enemy::die()
{
	_stateMachine->setState("die");

	this->notifyAllObserver(EntityObserverType::OnDie);
	this->dettachAllObject();
}

bool MyGame::Enemy::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getNode() != this && b->getNode() != this) return false;

	if (((a->getCollisionBitmask() == _physicsBody->getCollisionBitmask()) && (b->getCollisionBitmask() == Bitmask::BitmaskCollision::Player)) ||
		((a->getCollisionBitmask() == Bitmask::BitmaskCollision::Player) && (b->getCollisionBitmask() == _physicsBody->getCollisionBitmask())))
	{
		GameManager::getIns()->getCurrentMap()->handleZOrderObj(a->getNode(), b->getNode());
		return true;
	}

	return false;
}
