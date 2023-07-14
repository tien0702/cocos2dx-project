#ifndef __SCALER_H__
#define __SCALER_H__

#include "cocos2d.h"

USING_NS_CC;

class Scaler {
public:
	static void scaleByScreen(Node* node);
	static void updatePosition(Sprite* spriteOrigin);
	static void updateContentSize(Sprite* spriteOrigin);
	static Vec2 calculatePosition(const Vec2& originalPos);
	static Size calculateContentSize(const Size& originalSize);

	static void scaleNodeToFit(Node* node, Node* container, float margin);

private:
	static const float _contentScaleFactor;
};

#endif // !__SCALER_H__
