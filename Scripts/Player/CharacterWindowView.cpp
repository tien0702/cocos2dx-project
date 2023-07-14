#include "CharacterWindowView.h"

bool MyGame::CharacterWindowView::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	loadCompnent();

	DrawNode* drawNode = DrawNode::create();
	drawNode->drawRect(Vec2::ZERO, _windowSize, Color4F::WHITE);
	drawNode->drawSolidRect(Vec2::ZERO, _windowSize, Color4F(0, 0, 0, 0.5));
	drawNode->setPosition(_windowSize / -2);
	addChild(drawNode);
	this->addChild(_characterVisual);
	changeAnimation();

	this->schedule([&](float delta) {
		changeAnimation();
		}, 6.0f, "update_recovery");
	return true;
}

bool MyGame::CharacterWindowView::loadCompnent()
{
	AnimationCache* aniCache = AnimationCache::getInstance();
	std::string spriteFileName = Player::getIns()->getCharacter()->getSpriteFileName();
	SpriteFrame* frame = aniCache->getAnimation(spriteFileName + "-" + "idle")->getFrames().front()->getSpriteFrame();
	_characterVisual = Sprite::createWithSpriteFrame(frame);
	return true;
}

void MyGame::CharacterWindowView::changeAnimation()
{
	std::vector<std::string> aniDefault;
	aniDefault.push_back("idle");
	aniDefault.push_back("run");
	aniDefault.push_back("attack");

	int indexRand = RandomHelper::random_int(0, (int)aniDefault.size() - 1);
	
	_characterVisual->stopActionByTag(AniTag);
	std::string spriteFileName = Player::getIns()->getCharacter()->getSpriteFileName() + "-" + aniDefault.at(indexRand);
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);

	auto ani = RepeatForever::create(Animate::create(animation));
	ani->setTag(AniTag);
	_characterVisual->setFlippedX((RandomHelper::random_real(0.0f, 1.0f) > 0.5f));
	_characterVisual->runAction(ani);
}

bool MyGame::CharacterWindowView::isTouchInsideBackground(cocos2d::Touch* touch) {
	auto location = touch->getLocation();
	Rect rect;
	rect.size = _windowSize;
	rect.origin = _position - _windowSize / 2;
	auto backgroundBoundingBox = _characterVisual->getBoundingBox();
	return rect.containsPoint(location);
}

