#include "Scaler.h"

const float Scaler::_contentScaleFactor = Director::getInstance()->getContentScaleFactor();

void Scaler::scaleByScreen(Node* node)
{
    float scaler = Director::getInstance()->getContentScaleFactor();
    node->setScale(scaler);
}

void Scaler::updatePosition(Sprite* spriteOrigin) {
	auto newPos = Scaler::calculatePosition(spriteOrigin->getPosition());
	spriteOrigin->setPosition(newPos);
}

void Scaler::updateContentSize(Sprite* spriteOrigin) {
	auto newSize = Scaler::calculateContentSize(spriteOrigin->getContentSize());
	spriteOrigin->setContentSize(newSize);
}

Vec2 Scaler::calculatePosition(const Vec2& originalPos) {
	return Vec2(originalPos.x * _contentScaleFactor, originalPos.y * _contentScaleFactor);
}

Size Scaler::calculateContentSize(const Size& originalSize) {
	return Size(originalSize.width * _contentScaleFactor, originalSize.height * _contentScaleFactor);
}

void Scaler::scaleNodeToFit(Node* node, Node* container, float margin) {
    Size nodeSize = node->getContentSize();
    Size containerSize = container->getContentSize();

    float scale = 1.0f;

    // Scale to fit horizontally
    float horizontalScale = (containerSize.width - 2 * margin) / nodeSize.width;
    if (horizontalScale < scale) {
        scale = horizontalScale;
    }

    // Scale to fit vertically
    float verticalScale = (containerSize.height - 2 * margin) / nodeSize.height;
    if (verticalScale < scale) {
        scale = verticalScale;
    }

    // Set scale
    node->setScale(scale);
}