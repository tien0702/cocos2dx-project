#include "Gate.h"
#include "UI/Effect.h"
#include "Player/Player.h"
#include "Manager/GameManager.h"
#include "Map/GameMap.h"
#include "Chapter/Chapter.h"

bool MyGame::Gate::initWithValueMap(ValueMap val)
{
	if (!Sprite::create()) {
		log("Init Gate failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load properties Gate failed!");
		return false;
	}

	_mapPath += val["mapName"].asString();
	_effectName += val["effectName"].asString();
	_effectPath += _effectName;
	_mapName = val["mapName"].asString();

	Size size = Size(val["width"].asInt(), val["height"].asInt());
	Point pos = Point(val["x"].asInt(), val["y"].asInt());

	this->setPosition(pos + size / 2);
	this->setContentSize(size);


	if (!initAnimation()) {
		log("Init animation failed!");
	}

	this->scheduleUpdate();
	return true;
}

void MyGame::Gate::open()
{
	_open = true;
}

void MyGame::Gate::close()
{
	_open = false;
}

void MyGame::Gate::update(float dt)
{
	if (!_open) return;
	if (this->getBoundingBox().containsPoint(_player->getPosition()))
	{
		GameManager::getIns()->getChapter()->nextMap();
	}
}

bool MyGame::Gate::loadProperties()
{
	_mapPath = "Map/";
	_effectPath = "FHD/" + _effectPath;
	_player = Player::getIns()->getCharacter();
	return true;
}

bool MyGame::Gate::initAnimation()
{
	Animation* ani = AnimationCache::getInstance()->getAnimation(_effectName);
	if (ani == nullptr)
	{
		auto spriteCache = SpriteFrameCache::getInstance();
		spriteCache->addSpriteFramesWithFile(_effectPath + ".plist", _effectPath + ".png");
		ani = Effect::createAnimation(_effectName).first;
		//ani = Effect::createAnimation(_effectName, 20, 0.02f);
		AnimationCache::getInstance()->addAnimation(ani, _effectName);
	}
	this->initWithTexture(ani->getFrames().front()->getSpriteFrame()->getTexture());
	Animate* animate = Animate::create(ani->clone());
	animate->setDuration(1.5f);
	auto gateAni = RepeatForever::create(animate);
	this->runAction(gateAni);
	return true;
}
