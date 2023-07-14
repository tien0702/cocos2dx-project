#include "BounceLayer.h"
#include "HUDLayer.h"

BounceLayer* BounceLayer::create(Sprite* sprite, Color4B bgColor) {
    BounceLayer* layer = new (std::nothrow) BounceLayer();
    if (layer && layer->init(sprite, bgColor)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool BounceLayer::init(Sprite* sprite, Color4B bgColor) {
    if (!LayerColor::initWithColor(bgColor)) {
        return false;
    }

    _sprite = sprite;
    _sprite->removeFromParent();
    _sprite->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    this->addChild(_sprite);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BounceLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void BounceLayer::bounce(Sprite* sprite) 
{
    auto scene = Director::getInstance()->getRunningScene();
    if (scene) {
        auto layer = BounceLayer::create(sprite, Color4B(0, 0, 0, 128));
        scene->addChild(layer, INT_MAX);
    }
}

void BounceLayer::turnOff() {
    this->removeFromParentAndCleanup(true);
}

bool BounceLayer::onTouchBegan(Touch* touch, Event* event) {
    auto location = touch->getLocation();
    if (_sprite->getBoundingBox().containsPoint(location)) {
        return false;
    }
    this->turnOff();
    return true;
}