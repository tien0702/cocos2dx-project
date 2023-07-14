#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h" 

USING_NS_CC;

class Joystick : public Layer
{

public:
    virtual bool init();

    Point getVelocity() { return _velocity; }
    void resetJoystick();
    Size getSizeBG() { return _bgr->getContentSize(); }
    void setRenderer(Sprite* bgr, Sprite* thumb, Sprite* direction);
    void setThumbStatic(bool isStatic);
    void disable();
    void enable();
    void setStatic(bool isStatic) { this->_isStatic = isStatic; }
    void setOriginPos(Vec2 oPos) { this->_originPos = oPos; }
    void setRadiusChange(float radius) { this->_radiusChange = radius; }
    CREATE_FUNC(Joystick);
protected:
    Point _kCenter;
    Point _velocity;
    Sprite* _thumb;
    Sprite* _bgr;
    Sprite* _direction;
    bool _isPressed;
    bool _thumbStatic;
    bool _enable;

    float _joyRadius;
    float _thumbRadius;

    float _radiusChange = 200;


    Vec2 _originPos;
    bool _isStatic = true;

    virtual void updateVelocity(Point point);
    virtual bool onTouchBegan(Touch* pTouches, Event* pEvent);
    virtual bool handleLastTouch();
    virtual void TouchesMoved(Touch* pTouches, Event* pEvent);
    virtual void TouchCancelled(Touch* pTouch, Event* pEvent);
    virtual void TouchesEnded(Touch* pTouches, Event* pEvent);
};

#endif // !__JOYSTICK_H__
