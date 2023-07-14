#include "FloatingTextNofify.h"
#include "Manager/GameManager.h"

void MyGame::FloatingTextNotify::onScreenMiddle_Top(std::string content, Color3B color)
{
}

void MyGame::FloatingTextNotify::onPlayer_Middle(std::string content, Color3B color)
{
	Label* label = Label::createWithTTF(GameConfig::getIns()->getFont(), content);
	label->setColor(color);
	label->setPosition(FloatingTextNotify::getCharPositionOnMap());
	Director::getInstance()->getRunningScene()->addChild(label);
}

Vec2 MyGame::FloatingTextNotify::getCharPositionOnMap()
{
	Vec2 postionCharacter = GameManager::getIns()->getCharacter()->getPosition();
	return postionCharacter;
}
