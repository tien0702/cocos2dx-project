#include "FloatingNumber.h"
#include "ObjectTag.h"
#include "Chapter/ChapterMap.h"

MyGame::FloatingNumber* MyGame::FloatingNumber::_instance;

MyGame::FloatingNumber::FloatingNumber()
{
	_font = GameConfig::getIns()->getFont();
	_font.fontSize *= 0.6f;
	float timeScale = 0.2f;
	float scaleSize = 1.3f;
	auto zoomIN = ScaleBy::create(timeScale, scaleSize);
	auto zoomOut = zoomIN->reverse();
	_zoom = Sequence::createWithTwoActions(zoomIN, zoomOut);
	_zoom->retain();

}

MyGame::FloatingNumber* MyGame::FloatingNumber::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new FloatingNumber();
	}

	return _instance;
}

void MyGame::FloatingNumber::showDamage(Vec2 targetPos, DamageMessage* data)
{
	std::string dameStr = std::to_string(data->_amount);
	Label* dameLb = Label::createWithTTF(_font, dameStr);


	ElementType elementType = data->_elementType;
	switch (elementType)
	{
	case MyGame::PhysicalType:
		dameLb->setTextColor(Color4B::WHITE);
		break;
	case MyGame::PyroType:
		dameLb->setTextColor(Color4B::RED);
		break;
	case MyGame::CryoType:
		dameLb->setTextColor(Color4B::BLUE);
		break;
	case MyGame::LighningType:
		dameLb->setTextColor(Color4B(177, 36, 249, 255));
		break;
	default:
		dameLb->setTextColor(Color4B::WHITE);
		break;
	}


	float timeShow = RandomHelper::random_real(1.0f, 1.5f);
	int x = RandomHelper::random_int(-20, 20);
	int y = RandomHelper::random_int(10, 20);
	auto jump = JumpBy::create(timeShow, Vec2(x, 0), y, 1);
	auto remove = CallFunc::create([=]() {dameLb->removeFromParent(); });
	dameLb->runAction(Sequence::createWithTwoActions(jump, remove));

	if (data->_isCrit)
	{
		dameLb->runAction(_zoom->clone());
	}
	dameLb->setPosition(targetPos);
	Director::getInstance()->getRunningScene()->getChildByTag(ObjectTag::ChapterMap)->addChild(dameLb, SceneLayer::Effect);
}

void MyGame::FloatingNumber::healHeal(Vec2 targetPos, int amount)
{
	std::string dameStr = "+" + std::to_string(amount);
	Label* dameLb = Label::createWithTTF(_font, dameStr);
	dameLb->setTextColor(Color4B::GREEN);

	float timeShow = RandomHelper::random_real(1.0f, 1.5f);
	int x = RandomHelper::random_int(-20, 20);
	int y = RandomHelper::random_int(10, 20);

	auto jump = JumpBy::create(timeShow, Vec2(x, 0), y, 1);
	auto remove = CallFunc::create([=]() {dameLb->removeFromParent(); });
	dameLb->runAction(Sequence::createWithTwoActions(jump, remove));
	dameLb->setPosition(targetPos);
	Director::getInstance()->getRunningScene()->getChildByTag(ObjectTag::ChapterMap)->addChild(dameLb, SceneLayer::Effect);
}
