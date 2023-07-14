#ifndef __BOUNCE_LAYER_H__
#define __BOUNCE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class BounceLayer : public LayerColor {
public:
    static BounceLayer* create(Sprite* sprite, Color4B bgColor);
    void bounce(Sprite* sprite);
    void turnOff();

private:
    bool init(Sprite* sprite, Color4B bgColor);
    bool onTouchBegan(Touch* touch, Event* event);

    Sprite* _sprite;
};

#endif // !__BOUNCE_LAYER_H__
